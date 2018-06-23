<?php 

/**
 * Implements hook_sl7_payment_info().
 * 
 * Инициализирует способ оплаты.
 * 
 * controller - Класс контроллера оплаты. Смотрите файл sl7_payment.controller.inc
 * callback - Инициализация оплаты. Это может быть уход на внешний сайт для оплаты.
 * customer - Не обязательно. Если нужно собрать данные с плательщика для данного платежа.
 * Описываеться по Form API, но без входящих агрументов.
 * 
 * Примеры можете посмотреть в модулях:
 * 	sl7_invoice
 * 	sl7_receipt
 * 	sl7_robokassa
 * 	sl7_yandex_kassa
 */
function hook_sl7_payment_info() {
	
	$payment['sl7_invoice'] = array(
		'title' => 'Название',
		'description' => 'Описание',
		'controller' => 'SL7InvoicePaymentController',
		'callback' => 'sl7_invoice_callback',
		'customer' => 'sl7_invoice_customer', 
		'img' => drupal_get_path('module', 'sl7_invoice') . '/img/sl7_invoice.png',
	);
	
	return $payment;
}

/**
 * Implements hook_sl7_payment_after_enroll().
 * 
 * Отрабатывает после зачисления платежа.
 * 
 * @param SL7Order $order
 * 	Сущность платежа.
 * 	$order->data (array) - скрытые данные, которые можно передать в платёж.
 * 	Их видно в просмотре платежа.
 */
function hook_sl7_payment_after_enroll(SL7Order $order) {
	if ($order->data['destination'] == 'commerce') {
		$commerce_order = commerce_order_load($order->data['order_id']);
		commerce_order_status_update($commerce_order, 'processing', FALSE, NULL, 'Выбран тип оплаты.');
	}
}