<?php

/**
 * @file
 * SL7 Payment API.
 * 
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

function sl7_payment_get_controller($payment_type) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast[__FUNCTION__] = &drupal_static(__FUNCTION__);
  }
  $controller = &$drupal_static_fast[__FUNCTION__];

  if (!isset($controller)) {
    $payment_info = sl7_payment_get_info($payment_type);
    $class = $payment_info['controller'];
    $controller = new $class($payment_type);
  }

  drupal_alter(__FUNCTION__, $controller);

  return $controller;
}

/**
 * Получить информацию о типе платежа.
 *
 * @param null $payment_type
 *  Ничего или название типа платежа.
 * @return array
 *  Если аргумента $payment_type не пуст, вернётся массив с информацией платежа.
 *  Если аргумент пустой, то массив всех типов платежей, где ключ - это
 *  название платежа, а значение - массив с информацией о платеже.
 */
function sl7_payment_get_info($payment_type = NULL) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast[__FUNCTION__] = &drupal_static(__FUNCTION__);
  }
  $payments_info = &$drupal_static_fast[__FUNCTION__];

  if (!isset($payments_info)) {
    $payments_info = module_invoke_all('sl7_payment_info');

    foreach ($payments_info as $name => $info) {
      $payments_info[$name] += array(
        'controller' => 'SL7PaymentController',
      );
    }
  }

  drupal_alter(__FUNCTION__, $payments_info);

  if (array_key_exists($payment_type, $payments_info)) {
    return $payments_info[$payment_type];
  }

  return $payments_info;
}

/**
 * Получить стадию платежа.
 *
 * @param null $state
 *  Название типа платежа или ничего.
 * @return mixed
 *  Если входящий параметр не пуст, вернётся человекопонятное название текущей
 *  стадии платежа. Если такой стадии не существует, вернётся массив всех
 *  платежей. Если параметр пусть, будет возвращён массив всех стадий платежей.
 */
function sl7_payment_get_state($state = NULL) {
  $state_all = array(
    'pending' => 'В ожидании',
    'paid' => 'Оплачен',
    'expired' => 'Истёкший',
    'canceled' => 'Отменено',
  );

  if (array_key_exists($state, $state_all)) {
    return $state_all[$state];
  }

  return $state_all;
}

/**
 * Получить тип платежа.
 *
 * @param null $payment_type
 *  Ничего или название типа платежа.
 * @return array
 *  Если аргумента $payment_type не пуст, вернется человекопонятное название.
 *  Если аргумент пустой, то массив всех типов платежей, где ключ - это
 *  название платежа, а значение - человекопонятное название.
 */
function sl7_payment_get_type($payment_type = NULL) {
  $payments_info = sl7_payment_get_info();
  $payment_all = array();

  foreach ($payments_info as $name => $payment) {
    $payment_all[$name] = $payment['title'];
  }

  if (array_key_exists($payment_type, $payment_all)) {
    return $payment_all[$payment_type];
  }

  return $payment_all;
}