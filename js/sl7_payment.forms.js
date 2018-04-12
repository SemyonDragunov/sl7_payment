(function ($, Drupal, window, document, undefined) {

  $(document).ready(function() {

    $('body').on('click', '#sl7-payment .payment-pick', function() {

      function hasClass(el, cls) {
        return el.className && new RegExp("(\\s|^)" + cls + "(\\s|$)").test(el.className);
      }

      var payment_name = $(this).attr('id');
      var $form = $(this).closest('form');

      $form.find('input[name=payment_type]').val(payment_name);

      if (hasClass(this,'customer')) {
        $('#sl7-payment-type-customer-submit').mousedown();
      }
      if (!hasClass(this,'customer')) {
        $('#sl7-payment-type-submit').trigger('click');
      }
    });

  });

})(jQuery, Drupal, this, this.document);