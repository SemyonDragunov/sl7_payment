<?php

class sl7_payment_handler_sl7_order_pay_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['oid'] = 'oid';
    $this->additional_fields['enroll'] = 'enroll';
    $this->additional_fields['state'] = 'state';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $oid = $this->get_value($values, 'oid');
    $enroll = $this->get_value($values, 'enroll');
    $state = $this->get_value($values, 'state');

    if ($enroll == 0 && $state == 'pending') {
      return sl7_order_get_pay_link($oid);
    }

    return NULL;
  }
}