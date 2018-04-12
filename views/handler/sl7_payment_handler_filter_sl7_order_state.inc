<?php

class sl7_payment_handler_filter_sl7_order_state extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $states = sl7_payment_get_state();
      $this->value_options = $states;

      return $states;
    }
  }
}