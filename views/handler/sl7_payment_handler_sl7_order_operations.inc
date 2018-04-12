<?php

class sl7_payment_handler_sl7_order_operations extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['oid'] = 'oid';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $oid = $this->get_value($values, 'oid');
    $links = array();

    if (sl7_order_access('edit')) {
      $links['edit'] = array(
        'title' => t('Edit'),
        'href'  => SL7_ORDER_PATH . '/' . $oid . '/edit',
        'html'  => FALSE,
      );
      $links['edit']['query'] = drupal_get_destination();
    }

    if (sl7_order_access_enroll($oid)) {
      $links['enroll'] = array(
        'title' => 'Зачислить',
        'href'  => SL7_ORDER_PATH . '/' . $oid . '/enroll',
        'html'  => FALSE,
      );
      $links['enroll']['query'] = drupal_get_destination();
    }

    if (sl7_order_access('delete')) {
      $links['delete'] = array(
        'title' => t('Delete'),
        'href'  => SL7_ORDER_PATH . '/' . $oid . '/delete',
        'html'  => FALSE,
      );
      $links['delete']['query'] = drupal_get_destination();
    }

    return theme('links__ctools_dropbutton', array(
      'links' => $links,
      'attributes' => array(
        'class' => array('links', 'inline', 'operations')
      )
    ));
  }
}