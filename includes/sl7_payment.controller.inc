<?php

/**
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

interface SL7PaymentControllerInterface {
  public function __construct($payment_type);
  public function checkup();
  public function enroll($order);
}

interface SL7PaymentCustomerControllerInterface extends SL7PaymentControllerInterface {
  public function checkup_customer();
  public function set_customer(array $values);
}

/**
 * Class SL7PaymentController
 *
 * Класс по умолчанию для наследования другими платежными классами.
 */
class SL7PaymentController implements SL7PaymentControllerInterface {

  protected $payment_type;

  public function __construct($payment_type) {
    $this->payment_type = $payment_type;
  }

  /**
   * Проверка готовности счета к оплате.
   *
   * @return bool
   */
  public function checkup() {
    if (!empty($this->payment_type)) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Зачисление счета.
   */
  public function enroll($order) {
    $order = is_object($order) ? $order : sl7_order_load($order);
    $order->state = 'paid';
    $order->payment_type = $this->payment_type;
    $order->enroll = REQUEST_TIME;
    module_invoke_all('sl7_payment_after_enroll', $order);

    return sl7_order_save($order);
  }
}

/**
 * Class SL7PaymentCustomerController
 *
 * Класс для наследования платежными классами, у которых есть дополнительная
 * информация о плательщике.
 */
class SL7PaymentCustomerController extends SL7PaymentController implements SL7PaymentCustomerControllerInterface {

  protected $customer;

  public function __construct($payment_type) {
    parent::__construct($payment_type);
  }

  /**
   * Переопределяем SL7PaymentController::checkup().
   */
  public function checkup() {
    if (!empty($this->payment_type) && $this->checkup_customer()) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Проверка готовности данных о плательщике.
   *
   * @return bool
   */
  public function checkup_customer() {
    if (!empty($this->customer)) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Устанавливает данные о плательщике.
   *
   * @param array $values
   */
  public function set_customer(array $values) {
    foreach ($values as $name => $data) {
      $this->customer[$name] = isset($data['und']) && isset($data['und'][0]) ? $data['und'][0]['value'] : $data;
    }
  }
}