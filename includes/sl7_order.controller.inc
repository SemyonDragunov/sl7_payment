<?php
/**
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

/**
 * Class sl7_order entities.
 */
class SL7Order extends Entity {

  protected $item;

  public function __construct($values = array()) {
    parent::__construct($values, 'sl7_order');
  }

  protected function defaultLabel() {
    return $this->identifier();
  }

  protected function defaultUri() {
    return array('path' => $this->real_path());
  }

  public function real_path() {
    return SL7_ORDER_PATH . '/' . $this->identifier();
  }

  /**
   * Add to sl7_order once item (no save order and new item).
   */
  public function add_item($label, $amount, $quantity = 1, $unit = 'шт.') {
    $values = array();
    $values[] = array(
      'label' => $label,
      'amount' => round($amount, 2),
      'quantity' => round($quantity, 6),
      'unit' => $unit,
    );

    $this->add_item_multiple($values);
  }

  /**
   * Add to sl7_order many items (no save order and new item).
   */
  public function add_item_multiple(array $items) {
    foreach ($items as $item) {
      $this->item[] = sl7_order_item_create($item);
    }
  }

  /**
   * Override save().
   */
  public function save() {
    // Сохраняем ранее добавленные товары.
    $order = $this->wrapper();
    if (!empty($this->item)) {
      foreach ($this->item as $item) {
        $item->save();
        $order->sl7_order_item[] = $item->iid;
      }
    }

    return entity_get_controller($this->entityType)->save($this);
  }
}

/**
 * The Controller for sl7_order entities.
 */
class SL7OrderController extends EntityAPIControllerExportable {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  public function create(array $values = array()) {
    global $user;

    $values += array(
      'oid' => '',
      'is_new' => TRUE,
      'uid' => $user->uid,
      'recipient' => '',
      'state' => 'pending',
      'payment_type' => '',
      'enroll' => '',
      'data' => '',
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
    );

    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);

    field_attach_prepare_view('sl7_order', array($entity->oid => $entity), $view_mode, $langcode);
    entity_prepare_view('sl7_order', array($entity->oid => $entity), $langcode);
    $content += field_attach_view('sl7_order', $entity, $view_mode, $langcode);

    return $content;
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (empty($entity->is_new)) $entity->changed = REQUEST_TIME;
    return parent::save($entity, $transaction);
  }
}

/**
 * Class SL7Order metadata controller.
 */
class SL7OrderMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $properties = &$info[$this->type]['properties'];

    $properties['oid']['label'] = '№';
    $properties['oid']['description'] = 'Уникальный идентификатор платежа.';
    $properties['oid']['type'] = 'integer';

    $properties['uid'] = array(
      'label' => 'Создатель',
      'description' => 'Имя пользователя создателя платежа.',
      'getter callback' => 'sl7_order_metadata_field_uid',
      'type' => 'user',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    $properties['recipient'] = array(
      'label' => 'Получатель',
      'description' => 'Имя пользователя получателя платежа.',
      'getter callback' => 'sl7_order_metadata_field_recipient',
      'type' => 'user',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    $properties['created']['type'] = 'date';
    $properties['created']['label'] = 'Дата создания';
    $properties['created']['description'] = 'Время создания платежа.';

    $properties['changed']['type'] = 'date';
    $properties['changed']['label'] = 'Последние изменение';
    $properties['changed']['description'] = 'Дата и время последнего изменения платежа.';

    $properties['enroll']['type'] = 'date';
    $properties['enroll']['label'] = 'Дата зачисления';
    $properties['enroll']['description'] = 'Дата и время зачисления платежа.';

    $properties['payment_type'] = array(
      'label' => 'Способ оплаты',
      'description' => 'Способ оплаты.',
      'getter callback' => 'sl7_order_metadata_field_payment_type',
      'type' => 'text',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    $properties['state'] = array(
      'label' => 'Состояние',
      'description' => 'Состояние платежа.',
      'getter callback' => 'sl7_order_metadata_field_state',
      'type' => 'text',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    $properties['sum'] = array(
      'label' => 'Сумма',
      'description' => 'Общая сумма платежа.',
      'getter callback' => 'sl7_order_metadata_field_sum',
      'type' => 'decimal',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    return $info;
  }
}

class SL7OrderExtraFieldsController extends EntityDefaultExtraFieldsController {

  public function fieldExtraFields() {
    $extra_fields = array();

    $extra_fields['sl7_order']['sl7_order'] = array(
      'form' => array(
        'recipient' => array(
          'label' => 'Получатель',
          'description' => 'Имя пользователя получателя платежа.',
          'weight' => -9,
        ),
        'enroll' => array(
          'label' => 'Дата зачисления',
          'description' => 'Дата и время зачисления платежа.',
          'weight' => -6,
        ),
        'payment_type' => array(
          'label' => 'Способ оплаты',
          'description' => 'Способ оплаты.',
          'weight' => -5,
        ),
        'state' => array(
          'label' => 'Состояние',
          'description' => 'Состоние платежа.',
          'weight' => -4,
        ),
        'sum' => array(
          'label' => 'Сумма',
          'description' => 'Общая сумма платежа.',
          'weight' => -3,
        ),
      ),
      'display' => array(
        'recipient' => array(
          'label' => 'Получатель',
          'description' => 'Имя пользователя получателя платежа.',
          'weight' => -9,
        ),
        'enroll' => array(
          'label' => 'Дата зачисления',
          'description' => 'Дата и время зачисления платежа.',
          'weight' => -6,
        ),
        'payment_type' => array(
          'label' => 'Способ оплаты',
          'description' => 'Способ оплаты.',
          'weight' => -5,
        ),
        'state' => array(
          'label' => 'Состояние',
          'description' => 'Состоние платежа.',
          'weight' => -4,
        ),
        'sum' => array(
          'label' => 'Сумма',
          'description' => 'Общая сумма платежа.',
          'weight' => -3,
        ),
      ),
    );

    return $extra_fields;
  }
}

/**
 * Views controller for sl7_order entities.
 */
class SL7OrderViewsController extends EntityDefaultViewsController {

  public function views_data() {
    $data = parent::views_data();

    $data['sl7_order']['uid'] = array(
      'title' => 'Создатель',
      'help' => 'Имя пользователя создателя платежа.',
      'relationship' => array(
        'title' => 'Создатель',
        'help' => 'Имя пользователя создателя платежа.',
        'handler' => 'views_handler_relationship',
        'base' => 'users',
        'field' => 'uid',
        'label' => 'создатель',
      ),
      'field' => array(
        'handler' => 'views_handler_field_user',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_name',
      ),
    );
    $data['sl7_order']['recipient'] = array(
      'title' => 'Получатель',
      'help' => 'Имя пользователя получателя платежа.',
      'relationship' => array(
        'title' => 'Получатель',
        'help' => 'Имя пользователя получателя платежа.',
        'handler' => 'views_handler_relationship',
        'base' => 'users',
        'field' => 'uid',
        'label' => 'получатель',
      ),
      'field' => array(
        'handler' => 'views_handler_field_user',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_name',
      ),
    );
    $data['sl7_order']['state'] = array(
      'title' => 'Состояние',
      'help' => 'Состояние платежа.',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'sl7_payment_handler_filter_sl7_order_state',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
    $data['sl7_order']['payment_type'] = array(
      'title' => 'Способ оплаты',
      'help' => 'Способ оплаты.',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'sl7_payment_handler_filter_sl7_order_payment_type',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
    $data['sl7_order']['pay_link'] = array(
      'title' => 'Оплата счета',
      'help' => 'Ссылка на оплату счета.',
      'field' => array(
        'handler' => 'sl7_payment_handler_sl7_order_pay_link',
      ),
    );
    $data['sl7_order']['operations'] = array(
      'field' => array(
        'title' => 'Действия',
        'help' => 'Показывает все возможные операции над платежом.',
        'handler' => 'sl7_payment_handler_sl7_order_operations',
      ),
    );

    return $data;
  }
}

/**
 * Class sl7_order_item entities.
 */
class SL7OrderItem extends Entity {
  public function __construct($values = array()) {
    parent::__construct($values, 'sl7_order_item');
  }

  protected function defaultLabel() {
    return $this->label;
  }
}

/**
 * The Controller for sl7_order_item entities.
 */
class SL7OrderItemController extends EntityAPIController {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  public function create(array $values = array()) {
    $values += array(
      'iid' => '',
      'is_new' => TRUE,
      'label' => '',
      'quantity' => '1',
      'unit' => 'шт.',
      'amount' => '',
    );

    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);

    field_attach_prepare_view('sl7_order_item', array($entity->iid => $entity), $view_mode, $langcode);
    entity_prepare_view('sl7_order_item', array($entity->iid => $entity), $langcode);
    $content += field_attach_view('sl7_order_item', $entity, $view_mode, $langcode);

    return $content;
  }
}

class SL7OrderItemExtraFieldsController extends EntityDefaultExtraFieldsController {

  public function fieldExtraFields() {
    $extra_fields = array();

    $extra_fields['sl7_order_item']['sl7_order_item'] = array(
      'form' => array(
        'label' => array(
          'label' => 'Наименование',
          'description' => 'Наименование товара.',
          'weight' => -10,
        ),
        'quantity' => array(
          'label' => 'Количество',
          'description' => 'Количество товара.',
          'weight' => -9,
        ),
        'unit' => array(
          'label' => 'Единица измерения',
          'description' => 'Единица измерения количества товара.',
          'weight' => -8,
        ),
        'amount' => array(
          'label' => 'Цена',
          'description' => 'Цена товара.',
          'weight' => -7,
        ),
      ),
      'display' => array(
        'label' => array(
          'label' => 'Наименование',
          'description' => 'Наименование товара.',
          'weight' => -10,
        ),
        'quantity' => array(
          'label' => 'Количество',
          'description' => 'Количество товара.',
          'weight' => -9,
        ),
        'unit' => array(
          'label' => 'Единица измерения',
          'description' => 'Единица измерения количества товара.',
          'weight' => -8,
        ),
        'amount' => array(
          'label' => 'Цена',
          'description' => 'Цена товара.',
          'weight' => -7,
        ),
      ),
    );

    return $extra_fields;
  }
}

class SL7OrderItemInlineEntityFormController extends EntityInlineEntityFormController {

  public function defaultLabels() {
    $labels = array(
      'singular' => 'товар',
      'plural' => 'товары',
    );

    return $labels;
  }

  public function tableFields($bundles) {
    $fields = parent::tableFields($bundles);

    $fields['label']['label'] = 'Наименование';

    $fields['quantity'] = array(
      'type' => 'property',
      'label' => 'Количество',
      'weight' => 100,
    );
    $fields['unit'] = array(
      'type' => 'property',
      'label' => 'Единицы',
      'weight' => 101,
    );
    $fields['amount'] = array(
      'type' => 'property',
      'label' => 'Цена',
      'weight' => 102,
    );

    return $fields;
  }

  public function entityForm($entity_form, &$form_state) {
    $item = $entity_form['#entity'];

    $entity_form['label'] = array(
      '#type' => 'textfield',
      '#title' => 'Название',
      '#size' => 50,
      '#maxlength' => 255,
      '#default_value' => !empty($item->label) ? $item->label : '',
      '#required' => TRUE,
    );
    $entity_form['quantity'] = array(
      '#type' => 'textfield',
      '#title' => 'Количество',
      '#size' => 10,
      '#maxlength' => 20,
      '#default_value' => !empty($item->quantity) ? $item->quantity : 1,
      '#element_validate' => array('element_validate_number'),
      '#required' => TRUE,
    );
    $entity_form['unit'] = array(
      '#type' => 'textfield',
      '#title' => 'Ед.',
      '#size' => 10,
      '#maxlength' => 20,
      '#default_value' => !empty($item->unit) ? $item->unit : 'шт.',
      '#required' => TRUE,
    );
    $entity_form['amount'] = array(
      '#type' => 'textfield',
      '#title' => 'Цена',
      '#size' => 10,
      '#maxlength' => 20,
      '#default_value' => !empty($item->amount) ? $item->amount : '',
      '#element_validate' => array('element_validate_number'),
      '#required' => TRUE,
    );

    field_attach_form('sl7_order_item', $item, $entity_form, $form_state);

    return $entity_form;
  }

  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);
    $item = $entity_form['#entity'];
  }
}