<?php

class sl7_payment_handler_filter_sl7_order_payment_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $types = sl7_payment_get_type();
      $this->value_options = $types;

      return $types;
    }
  }
}