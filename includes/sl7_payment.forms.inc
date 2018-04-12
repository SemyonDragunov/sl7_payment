<?php

/**
 * @file
 *  Формы платежей.
 *  
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

/**
 * Форма оплаты.
 *
 * Массив $values.
 *
 * @code
 * array = (
 *  'oid' => '', // ID платежа. Если указан этот параметр, то остальные праметры
 *               // можно не указывать. Загрузиться существующий платеж.
 *  // Параметры для создания платежа. Все не обязательны.
 *  'uid' => '', // ID пользователя создавшего платеж. Если не указывать - текущий.
 *  'recipient' => '', // ID пользователя, которому предназначается платеж.
 *  'state' => '', // Статус платежа. Если не указывать - "Неоплачено".
 *  'item' => '', // Массив с товарами для платежа.
 * );
 * @endcode
 *
 * @see sl7_order_add_item()
 * @see sl7_order_add_item_multiple()
 *
 * Способы входящих параметров (Сортировка по приоритетам):
 *
 * 1 способ. Через $form_state['sl7_payment']:
 *  $form_state['sl7_payment']['values']
 *  $form_state['sl7_payment']['access_types']
 *  $form_state['sl7_payment']['access_mode']
 *
 * 2 спобос. Аргументы функции.
 *  См. аргументы функции.
 *
 * 3 способ. $_POST
 *  $_POST['values']
 *  $_POST['access_types']
 *  $_POST['access_mode']
 *
 * 4 способ. $_GET
 *  $_GET['values']
 *  $_GET['access_types']
 *  $_GET['access_mode']
 *
 * @param $form
 * @param $form_state
 * @param array $values
 *  Массив с входящими параметрами платежа.
 * @param array $access_types
 *  Массив со списком машинных названий проверяемых типов оплаты.
 * @param string $access_mode
 *  Режим доступа для типов оплаты:
 *    remove - типы оплаты указанные в $access_mode будут исключены из выбора.
 *    only - только те типы оплаты, что указаны в $access_mode буду доступны
 *    для выбора.
 * @return mixed
 */
function sl7_payment_form($form, &$form_state, array $values = NULL, array $access_types = NULL, $access_mode = 'remove') {
  $sl7_payment = &$form_state['sl7_payment'];

  // $form_state (priority) or function argument to $form_state
  $sl7_payment['values'] = !empty($sl7_payment['values']) ? $sl7_payment['values'] : $values;
  $sl7_payment['access_types'] = !empty($sl7_payment['access_types']) ? $sl7_payment['access_types'] : $access_types;
  $sl7_payment['access_mode'] = !empty($sl7_payment['access_mode']) ? $sl7_payment['access_mode'] : $access_mode;

  // POST request (priority) or $form_state to $form_state
  $sl7_payment['values'] = !empty($_POST['values']) ? $_POST['values'] : $sl7_payment['values'];
  $sl7_payment['access_types'] = !empty($_POST['access_types']) ? $_POST['access_types'] : $sl7_payment['access_types'];
  $sl7_payment['access_mode'] = !empty($_POST['access_mode']) ? $_POST['access_types'] : $sl7_payment['access_mode'];

  // GET request (priority) or $form_state to $form_state
  $sl7_payment['values'] = !empty($_GET['values']) ? $_GET['values'] : $sl7_payment['values'];
  $sl7_payment['access_types'] = !empty($_GET['access_types']) ? $_GET['access_types'] : $sl7_payment['access_types'];
  $sl7_payment['access_mode'] = !empty($_GET['access_mode']) ? $_GET['access_types'] : $sl7_payment['access_mode'];

  // Проверка входящих данных.
  if (!$sl7_payment['values']) {
    $sl7_payment['message'] = 'Ошибка входных данных платежа.';
    $sl7_payment['stage'] = 'message';
  }

  // Если JSON.
  if (is_string($sl7_payment['values'])) {
    if ($decode_values = json_decode($sl7_payment['values'])) {
      $sl7_payment['values'] = SL7ApiArray::objectToArray($decode_values);
    }
  }

  // Если access_mode = only и пустой массив самих доступных типов оплат.
  if (empty($sl7_payment['access_types']) && $sl7_payment['access_mode'] == 'only') {
    $sl7_payment['message'] = 'Ошибка входных данных доступа.';
    $sl7_payment['stage'] = 'message';
  }

  sl7_payment_form_prepare_object($form, $form_state);
  if (!isset($sl7_payment['payments_info'])) $sl7_payment['payments_info'] = sl7_payment_get_info();
  if (!isset($sl7_payment['stage'])) $sl7_payment['stage'] = 'types';
  if (!isset($sl7_payment['message'])) $sl7_payment['message'] = NULL;

  // Закрываем возможность оплаты для соответствующих статусов.
  switch($sl7_payment['object']->state) {
    case 'paid':
      $sl7_payment['message'] = 'Счёт уже оплачен.';
      $sl7_payment['stage'] = 'message';
      break;

    case 'expired':
      $sl7_payment['message'] = 'Истёк срок платежа.';
      $sl7_payment['stage'] = 'message';
      break;

    case 'canceled':
      $sl7_payment['message'] = 'Оплата по этому счёту невозможна.';
      $sl7_payment['stage'] = 'message';
      break;
  }

  // Убираем из выбора запрещенные к показу типы оплаты.
  $default_values = variable_get('sl7_payment_method_access');
  foreach ($sl7_payment['payments_info'] as $name => $type) {
    if (!isset($default_values[$name])) {
      unset($sl7_payment['payments_info'][$name]);
    }
  }

  // Если доступен только 1 способ оплаты, переходим к нему сразу.
  if (count($method = variable_get('sl7_payment_method_access')) == 1) {
    $sl7_payment['payment_type'] = current($method);
    sl7_payment_form_customer_or_go($form, $form_state);
  }

  $form['#prefix'] = '<div id="sl7-payment">';
  $form['#suffix'] = '</div>';
  $form['actions'] = array('#type' => 'actions');
  // Перехват управления функцией
  $form['#submit'] = array('sl7_payment_form_submit');
  $form['#attached'] = array(
    'js' => array(
      drupal_get_path('module', 'sl7_payment') . '/js/sl7_payment.forms.js',
    ),
    'css' => array(
      drupal_get_path('module', 'sl7_payment') . '/css/sl7_payment.forms.css',
    ),
  );

  switch ($sl7_payment['stage']) {
    case 'types':
    default:
      return sl7_payment_select_type_form($form, $form_state);
      break;

    case 'customer';
      return sl7_payment_customer_get_form($form, $form_state);
      break;

    case 'message';
      return sl7_payment_message_form($form, $form_state);
      break;
  }
}

/**
 * Получение customer формы для типа платежа.
 *
 * @param $form
 * @param $form_state
 * @param null $payment_type
 * @return array|bool|mixed
 */
function sl7_payment_customer_get_form($form, &$form_state, $payment_type = NULL) {
  $form['#token'] = FALSE;

  if (empty($payment_type)) {
    if (!empty($form_state['sl7_payment']['payment_type'])) {
      $payment_type = $form_state['sl7_payment']['payment_type'];
    }
    else {
      return FALSE;
    }
  }

  if (!$form_state['sl7_payment']['payments_info']) {
    $form_state['sl7_payment']['payments_info'] = sl7_payment_get_info();
  }
  $payment_info = $form_state['sl7_payment']['payments_info'][$payment_type];
  $customer_form_id = $payment_info['customer'];
  $form = call_user_func($customer_form_id);

  // Если в массиве $form_state['sl7_payment']['customer'] присутствует
  // заполненое поле из customer_form платежа - убираем.
  if (isset($form_state['sl7_payment']['customer'])) {
    foreach ($form as $name => $value) {
      if (array_key_exists($name, $form_state['sl7_payment']['customer'])) {
        unset($form[$name]);
      }
    }
  }

  $form['actions']['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Продолжить',
  );

  // Если определён дополнительный customer validate, то добавляем его.
  if (function_exists($customer_form_id . '_validate')) {
    $form['#validate'][] = $customer_form_id . '_validate';
  }

  // Возвращение правильно сабмита.
  $form['#submit'] = array('sl7_payment_form_submit');

  return $form;
}

/**
 * Error form.
 */
function sl7_payment_message_form($form, &$form_state) {
  $form['#token'] = FALSE;

  $form['message_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('sl7-event-message'),
    ),
  );

  $form['message_container']['message'] = array(
    '#markup' => $form_state['sl7_payment']['message'],
  );

  return $form;
}

/**
 * Payment types form.
 */
function sl7_payment_select_type_form($form, &$form_state) {
  $form['#token'] = FALSE;

  foreach ($form_state['sl7_payment']['payments_info'] as $name => $settings) {
    $payment_controller = sl7_payment_get_controller($name);

    // Проверка доступа способа оплаты. Зависит от входящих параметров формы.
    if (!empty($form_state['sl7_payment']['access_types'])) {
      switch ($form_state['sl7_payment']['access_mode']) {
        case 'only':
          if (!in_array($name, $form_state['sl7_payment']['access_types'])) {
            continue 2;
          }
          break;

        case 'remove':
        default:
          if (in_array($name, $form_state['sl7_payment']['access_types'])) {
            continue 2;
          }
          break;
      }
    }

    $form[$name] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => array($name),
        'class' => array('payment-pick'),
      ),
    );
    if (method_exists($payment_controller, 'checkup_customer')) {
      $form[$name]['#attributes']['class'][] = 'customer';
    }
    $form[$name]['img'] = array(
      '#type' => 'item',
      '#markup' => '<img src="/' . $settings['img'] . '">',
      '#prefix' => '<div class="img"><div class="v-outer"><div class="v-inner">',
      '#suffix' => '</div></div></div>',
    );
    $form[$name]['text'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('text'),
      ),
    );
    $form[$name]['text']['name'] = array(
      '#type' => 'item',
      '#markup' => '<div class="name">' . check_plain($settings['title']) . '</div>',
    );
    $form[$name]['text']['description'] = array(
      '#type' => 'item',
      '#markup' => '<p>' . check_plain($settings['description']) . '</p>',
    );
  }

  $form['payment_type'] = array(
    '#type' => 'hidden',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'pay',
    '#id' => 'sl7-payment-type-submit',
    '#attributes' => array(
      'class' => array('element-invisible'),
    ),
  );

  $form['actions']['customer'] = array(
    '#type' => 'submit',
    '#value' => 'customer',
    '#id' => 'sl7-payment-type-customer-submit',
    '#attributes' => array(
      'class' => array('element-invisible'),
    ),
    '#ajax' => array(
      "callback" => "sl7_payment_form_ajax_submit",
      "wrapper" => "sl7-payment",
      "effect" => "slide",
      'method' => 'replace',
      'progress' => array('type' => 'none'),
    ),
  );

  return $form;
}

function sl7_payment_form_ajax_submit($form, &$form_state) {
  return $form;
}

function sl7_payment_form_submit($form, &$form_state) {
  $sl7_payment = &$form_state['sl7_payment'];

   switch ($sl7_payment['stage']) {
    case 'types':
      $sl7_payment['payment_type'] = $form_state['values']['payment_type'];
      sl7_payment_form_customer_or_go($form, $form_state);
      break;

    case 'customer':
      $sl7_payment['customer'] = $sl7_payment['customer'] + $form_state['values'];

      $payment_controller = sl7_payment_get_controller($sl7_payment['payment_type']);
      $payment_controller->set_customer($sl7_payment['customer']);

      sl7_order_save($sl7_payment['object']);
      $callback = $sl7_payment['payments_info'][$sl7_payment['payment_type']]['callback'];
      call_user_func_array($callback, array($sl7_payment['object']));
      break;
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];

  $form_state['rebuild'] = TRUE;
}

function sl7_payment_form_customer_or_go($form, &$form_state) {
  $sl7_payment = &$form_state['sl7_payment'];
  $payment_controller = sl7_payment_get_controller($sl7_payment['payment_type']);

  // Если тип платежа с дополнительными данными.
  if (method_exists($payment_controller, 'checkup_customer') && isset($sl7_payment['payments_info'][$sl7_payment['payment_type']]['customer'])) {
    if (isset($sl7_payment['customer'])) {
      $payment_controller->set_customer($sl7_payment['customer']);
    }
    else {
      $sl7_payment['customer'] = array();
    }
    $sl7_payment['stage'] = 'customer';

    // Если дополнительные данные с формы, полностью удовлетворили требования,
    // то не показываем форму доп. данных, а продолжаем.
    if ($payment_controller->checkup_customer()) {
      sl7_order_save($sl7_payment['object']);
      $callback = $sl7_payment['payments_info'][$sl7_payment['payment_type']]['callback'];
      call_user_func_array($callback, array($sl7_payment['object']));
    }
  }
  // Иначе завершаем.
  else {
    if (empty($sl7_payment['object']->oid)) {
      sl7_order_save($sl7_payment['object']);
    }
    $callback = $sl7_payment['payments_info'][$sl7_payment['payment_type']]['callback'];
    call_user_func_array($callback, array($sl7_payment['object']));
  }
}

/**
 * Подготовка объекта для платежа.
 */
function sl7_payment_form_prepare_object($form, &$form_state) {
  $sl7_payment = &$form_state['sl7_payment'];

  if (empty($sl7_payment['object'])) {
    if (empty($sl7_payment['values']['oid'])) {
      $order = sl7_order_create();
      if (!empty($sl7_payment['values']['uid'])) {
        $order->uid = $sl7_payment['values']['uid'];
      }
      if (!empty($sl7_payment['values']['recipient'])) {
        $order->recipient = $sl7_payment['values']['recipient'];
      }
      if (!empty($sl7_payment['values']['state'])) {
        $order->state = $sl7_payment['values']['state'];
      }
      if (!empty($sl7_payment['values']['data'])) {
        $order->data = $sl7_payment['values']['data'];
      }
      if (!empty($sl7_payment['values']['item'])) {
        $order->add_item_multiple($sl7_payment['values']['item']);
      }
      $sl7_payment['object'] = $order;
    }
    else {
      $sl7_payment['object'] = sl7_order_load($sl7_payment['values']['oid']);
    }
  }
}