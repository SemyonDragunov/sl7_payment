<?php
/**
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

/**
 * UI controller for sl7_order.
 */
class SL7OrderUIController extends EntityDefaultUIController {

  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%sl7_order';

    $items[$this->path . '/view'] = array(
      'title'  => 'Все платежи',
      'type'   => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    $items[$this->path . '/add'] = array(
      'title'            => 'Создать платеж',
      'page callback'    => 'sl7_order_get_form',
      'page arguments'   => array('create', NULL),
      'access callback'  => 'sl7_order_access',
      'access arguments' => array('create'),
      'type'             => MENU_LOCAL_TASK,
      'weight'           => -9,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file'             => 'sl7_order.ui.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']) . '/includes',
    );

    $items[$this->path . '/' . $wildcard] = array(
      'title callback'   => 'sl7_order_page_title',
      'title arguments'  => array($id_count),
      'page callback'    => 'entity_ui_entity_page_view',
      'page arguments'   => array($id_count),
      'load arguments'   => array($this->entityType),
      'access callback'  => 'sl7_order_access',
      'access arguments' => array('view', $id_count),
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file'             => 'sl7_order.ui.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']) . '/includes',
    );

    $items[$this->path . '/' . $wildcard . '/view'] = array(
      'title'   => t('View'),
      'type'    => MENU_DEFAULT_LOCAL_TASK,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'weight'  => -10,
    );

    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title'            => t('Edit'),
      'page callback'    => 'sl7_order_get_form',
      'page arguments'   => array('edit', $id_count),
      'load arguments'   => array($this->entityType),
      'access callback'  => 'sl7_order_access',
      'access arguments' => array('edit'),
      'file'             => 'sl7_order.ui.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']) . '/includes',
      'type'             => MENU_LOCAL_TASK,
      'weight'           => -9,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/' . $wildcard . '/enroll'] = array(
      'title'            => 'Зачислить',
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array('sl7_order_enroll_form', $id_count),
      'load arguments'   => array($this->entityType),
      'access callback'  => 'sl7_order_access_enroll',
      'access arguments' => array($id_count),
      'type'             => MENU_LOCAL_TASK,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'weight'           => -8,
      'file'             => 'sl7_order.ui.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']) . '/includes',
    );

    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title'            => t('Delete'),
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array('sl7_order_delete_form', $id_count),
      'load arguments'   => array($this->entityType),
      'access callback'  => 'sl7_order_access',
      'access arguments' => array('delete', $id_count),
      'type'             => MENU_LOCAL_TASK,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'weight'           => -7,
      'file'             => 'sl7_order.ui.inc',
      'file path'        => drupal_get_path('module', $this->entityInfo['module']) . '/includes',
    );

    return $items;
  }

  public function form($form, &$form_state) {

    $order = $form_state['sl7_order'];
    $recipient = user_load($order->recipient);
    $author = user_load($order->uid);

    $form['recipient'] = array(
      '#type'              => 'textfield',
      '#title'             => 'Получатель',
      '#description'       => 'Если поле оставить пустым, автором будет Гость.',
      '#default_value'     => !empty($recipient->name) ? $recipient->name : '',
      '#autocomplete_path' => 'user/autocomplete',
      '#element_validate'  => array('sl7_order_user_name_validate'),
      '#required'          => FALSE,
    );

    $form['state'] = array(
      '#type'          => 'select',
      '#title'         => 'Состояние',
      '#options'       => sl7_payment_get_state(),
      '#default_value' => isset($order->state) ? $order->state : 'pending',
      '#required'      => TRUE,
    );

    field_attach_form('sl7_order', $order, $form, $form_state);

    $form['tabs'] = array(
      '#type' => 'vertical_tabs',
      '#weight' => 50,
    );
    $form['editing_info'] = array(
      '#type' => 'fieldset',
      '#title' => 'Информация о редактировании',
      '#group' => 'tabs',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['editing_info']['uid'] = array(
      '#type'              => 'textfield',
      '#title'             => 'Создатель',
      '#description'       => 'Если поле оставить пустым, автором будет Гость.',
      '#default_value'     => !empty($author->name) ? $author->name : '',
      '#autocomplete_path' => 'user/autocomplete',
      '#element_validate'  => array('sl7_order_user_name_validate'),
    );
    $form['editing_info']['created'] = array(
      '#type' => 'textfield',
      '#title'             => 'Время создания',
      '#default_value'     => format_date($order->created, 'short'),
      '#disabled'          => TRUE,
      '#required'          => TRUE,
    );
    $form['editing_info']['changed'] = array(
      '#type' => 'textfield',
      '#title'             => 'Время последнего изменения',
      '#default_value'     => format_date($order->changed, 'short'),
      '#disabled'          => TRUE,
      '#required'          => TRUE,
    );
    $form['data'] = array(
      '#type' => 'fieldset',
      '#title' => 'Данные платежа',
      '#group' => 'tabs',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['data']['data'] = array(
      '#markup' => '<pre><code>' . print_r($order->data, true) . '</code></pre>',
    );

    $form['actions'] = array(
      '#type' => 'actions',
    );
    $form['actions']['submit'] = array(
      '#type'   => 'submit',
      '#value'  => !empty($order->oid) ? 'Сохранить' : 'Создать',
      '#weight' => 0,
    );
    $form['actions']['delete'] = array(
      '#markup' => !empty($order->oid) ? l(t('Delete'), SL7_ORDER_PATH . '/' . $order->oid . '/delete', array('attributes' => array('class' => array('button remove')), 'query' => array('destination' => SL7_ORDER_PATH))) : '',
    );

    return $form;
  }

  public function formValidate($form, &$form_state) {

  }

  public function formSubmit($form, &$form_state) {
    $order = $this->entityFormSubmitBuildEntity($form, $form_state);
    $order->save();

    if (!empty($order->is_new)) {
      $form_state['redirect'] = $order->real_path();
      drupal_set_message("Платеж № $order->oid создан.");
    }
    else {
      $form_state['redirect'] = SL7_ORDER_PATH;
      drupal_set_message("Платеж № $order->oid сохранен.");
    }
  }

  public function deleteForm($form, &$form_state) {
    $order = $form_state['sl7_order'];

    $form = confirm_form($form,
      "Вы уверены в удалении платежа № $order->oid?",
      SL7_ORDER_PATH,
      '<p>' . 'Удаление не может быть отменено.' . '</p>',
      t('Delete'),
      t('Cancel'),
      'confirm'
    );

    return $form;
  }

  public function deleteFormSubmit($form, &$form_state) {
    $order = $form_state['sl7_order'];

    sl7_order_delete($order);

    $message = "Платеж № $order->oid удален.";
    drupal_set_message($message);

    $form_state['redirect'] = SL7_ORDER_PATH;
  }

  public function enrollForm($form, &$form_state) {
    $order = $form_state['sl7_order'];

    $form['payment_type'] = array(
      '#title'         => 'Способ зачисления',
      '#type'          => 'select',
      '#options'       => sl7_payment_get_type(),
      '#default_value' => key(sl7_payment_get_type()),
      '#access'        => count(sl7_payment_get_type()) > 1,
      '#required'      => TRUE,
    );

    $form += confirm_form($form,
      "Зачислить платеж № $order->oid?",
      SL7_ORDER_PATH,
      '<p>' . "Зачислить платеж № $order->oid?" . '</p>',
      'Зачислить',
      t('Cancel'),
      'confirm'
    );

    return $form;
  }

  public function enrollFormSubmit($form, &$form_state) {
    $order = $form_state['sl7_order'];
    $payment_type = $form_state['values']['payment_type'];

    sl7_payment_get_controller($payment_type)->enroll($order);

    $message = "Платеж № $order->oid зачислен.";
    drupal_set_message($message);

    $form_state['redirect'] = SL7_ORDER_PATH;
  }
}

function sl7_order_edit_form($form, &$form_state) {
  return entity_ui_controller($form_state['entity_type'])->form($form, $form_state);
}

function sl7_order_edit_form_validate($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->formValidate($form, $form_state);
}

function sl7_order_edit_form_submit($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->formSubmit($form, $form_state);
}

function sl7_order_delete_form($form, &$form_state, $order) {
  $entity_type = 'sl7_order';
  $form_state['entity_type'] = $entity_type;
  $form_state[$entity_type] = $order;
  return entity_ui_controller($form_state['entity_type'])->deleteForm($form, $form_state);
}

function sl7_order_delete_form_submit($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->deleteFormSubmit($form, $form_state);
}

function sl7_order_enroll_form($form, &$form_state, $order) {
  $entity_type = 'sl7_order';
  $form_state['entity_type'] = $entity_type;
  $form_state[$entity_type] = $order;
  return entity_ui_controller($form_state['entity_type'])->enrollForm($form, $form_state);
}

function sl7_order_enroll_form_submit($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->enrollFormSubmit($form, $form_state);
}

function sl7_order_get_form($op = 'create', $order = NULL) {
  $form_state = array(
    'entity_type' => 'sl7_order',
    'op' => $op,
  );

  switch ($op) {
    case 'create':
      drupal_set_title('Создать платеж');
      $form_state['sl7_order'] = sl7_order_create();
      break;
    case 'edit':
      $form_state['sl7_order'] = is_object($order) ? $order : sl7_order_load($order);
      break;
    default:
      $form_state['sl7_order'] = $order;
      break;
  }

  form_load_include($form_state, 'inc', 'sl7_order', 'includes/sl7_order.ui');

  $form_state['build_info']['args'] = array($op, $order);

  return drupal_build_form('sl7_order_edit_form', $form_state);
}

function sl7_order_page_title(SL7Order $order){
  return 'Счет № ' . $order->oid . ' от ' . date('d.m.Y', $order->created);
}