<?php

/**
 * @file
 * API for sl7_order & sl7_order_item entities.
 * 
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

function sl7_order_access($op, $order = NULL, $account = NULL) {
  $rights = &drupal_static(__FUNCTION__, array());

  if (!empty($account)) {
    $account = is_object($account) ? $account : user_load($account);
  }
  else {
    $account = $GLOBALS['user'];
  }

  // User #1 has all privileges.
  if ($account->uid == 1) {
    return TRUE;
  }

  if (!$order) {
    if ($op == 'create' && user_access("sl7_order $op", $account)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  if ($order) {
    $order = is_object($order) ? $order : sl7_order_load($order);
    $oid = $order->oid;
  }

  if (isset($rights[$account->uid][$oid][$op])) {
    return $rights[$account->uid][$oid][$op];
  }

  if (user_access('administer sl7_payment', $account)) {
    $rights[$account->uid][$oid][$op] = TRUE;
    return TRUE;
  }

  if ('view' == $op && $order) {
    if (user_access("sl7_order any $op", $account)) {
      $rights[$account->uid][$oid][$op] = TRUE;
      return TRUE;
    }
    if (user_access("sl7_order recipient $op", $account) && $order->recipient == $account->uid) {
      $rights[$account->uid][$oid][$op] = TRUE;
      return TRUE;
    }
    if (user_access("sl7_order own $op", $account) && $order->uid == $account->uid) {
      $rights[$account->uid][$oid][$op] = TRUE;
      return TRUE;
    }
  }

  if (user_access("sl7_order $op", $account)) {
    $rights[$account->uid][$oid][$op] = TRUE;
    return TRUE;
  }

  return FALSE;
}

/**
 * Проверка доступа на страницу личного кабинета.
 */
function sl7_order_access_user_page($current_user) {
  $account = $GLOBALS['user'];

  // User #1 has all privileges:
  if ($account->uid == 1) {
    return TRUE;
  }

  if (user_access('sl7_order any view', $account)) {
    return TRUE;
  }

  if (user_access('sl7_order own view', $account) && $current_user->uid == $account->uid) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Проверка доступа для зачисления платежа.
 *
 * @param null $order
 *  Order ID или объект SL7Order.
 * @param null $account
 * @return bool
 */
function sl7_order_access_enroll($order = NULL, $account = NULL) {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }

  $order = is_object($order) ? $order : sl7_order_load($order);

  $states = array('paid', 'canceled', 'expired');
  if (in_array($order->state, $states)) {
    return FALSE;
  }

  // User #1 has all privileges:
  if ($account->uid == 1) {
    return TRUE;
  }

  if ((user_access('sl7_order enroll', $account) || user_access('administer sl7_payment', $account))) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

function sl7_order_create($values = array()) {
  return entity_get_controller('sl7_order')->create($values);
}

function sl7_order_load($order_ids, $reset = FALSE) {
  $order = sl7_order_load_multiple(array($order_ids), array(), $reset);
  return reset($order);
}

function sl7_order_load_multiple($order_ids = array(), $conditions = array(), $reset = FALSE) {
  $order_ids = ($order_ids) ? $order_ids : FALSE;
  return entity_load('sl7_order', $order_ids, $conditions, $reset);
}

function sl7_order_delete(SL7Order $order) {
  $order->delete();
}

function sl7_order_delete_multiple(array $oids) {
  entity_get_controller('sl7_order')->delete($oids);
}

/**
 * Добавление в существующий платеж новый одиночный товар.
 *
 * @param $oid
 *  ID платежа.
 * @param $label
 *  Название товара.
 * @param $amount
 *  Цена товара за 1 quantity. Максимально два десятичных знака *.99
 * @param int $quantity
 *  Количество товаров. Максимальный формат 99.999999
 * @param string $unit
 *  Единица измерения товара.
 * @return object SL7Order
 */
function sl7_order_add_item($oid, $label, $amount, $quantity = 1, $unit = 'шт.') {
  $order = sl7_order_load($oid);
  $order->add_item($label, $amount, $quantity, $unit);
  $order->save();
  return $order;
}

/**
 * Добавление много новых товаров в существующий платеж.
 *
 * @code
 * array(
 *  array(
 *    'label' => '',
 *    'amount' => '',
 *    'quantity' => '',
 *    'unit' => '',
 *  ),
 * );
 * @endcode
 *
 * @see sl7_order_add_item()
 *
 * @param $oid
 *  ID платежа.
 * @param array $values
 *  Массив с данными товаров.
 * @return object SL7Order
 */
function sl7_order_add_item_multiple($oid, array $values) {
  $order = sl7_order_load($oid);
  $order->add_item_multiple($values);
  $order->save();
  return $order;
}

function sl7_order_save(SL7Order $order) {
  return entity_save('sl7_order', $order);
}

/**
 * Зачисление счета оперделённым типом оплаты.
 *
 * @param $order
 *  Object sl7_order entity or sl7_order->oid
 * @param $payment_type
 *  Name of type payment
 *
 * @return bool
 */
function sl7_order_enroll($order, $payment_type) {
  return sl7_payment_get_controller($payment_type)->enroll($order);
}
/**
 * Зачисление счета оперделённым типом оплаты. С проверкой суммы оплаты.
 *
 * @param $order
 *  Object sl7_order entity or sl7_order->oid
 * @param $payment_type
 *  Name of type payment
 * @param $sum
 *  Сумма для проверки.
 *
 * @return bool
 */
function sl7_order_enroll_check_sum($order, $payment_type, $sum) {
  $order = is_object($order) ? $order : sl7_order_load($order);
  $sum = (integer) $sum;

  if (sl7_order_get_sum($order) == $sum) {
    return sl7_payment_get_controller($payment_type)->enroll($order);
  }

  return FALSE;
}

/**
 * Путь до платежа.
 */
function sl7_order_uri(SL7Order $order){
  return array(
    'path' => $order->real_path(),
  );
}

/**
 * Получить ссылку на оплату счета.
 * @param $oid
 *  Object sl7_order entity or sl7_order->oid
 * @return string
 */
function sl7_order_get_pay_link($oid) {
  $oid = is_object($oid) ? $oid->oid : $oid;

  $link = array(
    '#theme' => 'link',
    '#text' => 'Оплатить',
    '#path' => "payment/pay",
    '#options' => array(
      'attributes' => array(),
      'html' => TRUE,
      'query' => array(
        'values' => array(
          'oid' => $oid,
        ),
      ),
    ),
  );

  return render($link);
}

/**
 * Получить общую сумму счета.
 *
 * @param $order
 * @return int
 */
function sl7_order_get_sum($order) {
  $order = is_object($order) ? $order : sl7_order_load($order);
  $items = entity_metadata_wrapper('sl7_order', $order)->sl7_order_item->value();
  $sum = 0;
  foreach ($items as $item) {
    $sum += $item->quantity*$item->amount;
  }

  return $sum;
}

/**
 * Получение всех товаров счета.
 *
 * @param $order
 *  Или OID или объект.
 * @return mixed
 */
function sl7_order_get_items($order) {
  $order = is_object($order) ? $order : sl7_order_load($order);
  $items = $order->wrapper()->sl7_order_item->value();

  foreach ($items as $key => $item) {
    $items[$key] = (array) $item;
  }

  return $items;
}

/**
 * API for sl7_order_item entities.
 */

function sl7_order_item_create($values = array()) {
  return entity_get_controller('sl7_order_item')->create($values);
}