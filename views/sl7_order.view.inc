<?php

/**
 * @file
 * View sl7_order.
 */

$view = new view();
$view->name = 'sl7_order';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'sl7_order';
$view->human_name = 'Платежи';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['use_more_text'] = 'ещё';
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Применить';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
$handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Сортировать по';
$handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'По возрастанию';
$handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'По убыванию';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
$handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
$handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'oid' => 'oid',
  'created' => 'created',
  'state' => 'state',
  'sum' => 'sum',
  'pay_link' => 'pay_link',
);
$handler->display->display_options['style_options']['default'] = 'oid';
$handler->display->display_options['style_options']['info'] = array(
  'oid' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'created' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'state' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'sum' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'pay_link' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 1,
  ),
);
$handler->display->display_options['style_options']['sticky'] = TRUE;
/* Поле: Обработчик испорчен или отсутствует */
$handler->display->display_options['fields']['oid']['id'] = 'oid';
$handler->display->display_options['fields']['oid']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['oid']['field'] = 'oid';
/* Поле: Платеж: Создатель */
$handler->display->display_options['fields']['uid_1']['id'] = 'uid';
$handler->display->display_options['fields']['uid_1']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['uid_1']['field'] = 'uid';
$handler->display->display_options['fields']['uid_1']['link_to_entity'] = 1;
$handler->display->display_options['fields']['uid_1']['view_mode'] = 'full';
$handler->display->display_options['fields']['uid_1']['bypass_access'] = 0;
/* Поле: Платеж: Дата создания */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'sl7_order';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['label'] = 'Создано';
$handler->display->display_options['fields']['created']['date_format'] = 'custom';
$handler->display->display_options['fields']['created']['custom_date_format'] = 'd.m.Y H:i';
$handler->display->display_options['fields']['created']['second_date_format'] = 'long';
/* Поле: Платеж: Состояние */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['link_to_entity'] = 0;
/* Поле: Платеж: Сумма */
$handler->display->display_options['fields']['sum']['id'] = 'sum';
$handler->display->display_options['fields']['sum']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['sum']['field'] = 'sum';
$handler->display->display_options['fields']['sum']['set_precision'] = TRUE;
$handler->display->display_options['fields']['sum']['precision'] = '2';
$handler->display->display_options['fields']['sum']['link_to_entity'] = 0;
/* Поле: Платеж: Дата зачисления */
$handler->display->display_options['fields']['enroll']['id'] = 'enroll';
$handler->display->display_options['fields']['enroll']['table'] = 'sl7_order';
$handler->display->display_options['fields']['enroll']['field'] = 'enroll';
$handler->display->display_options['fields']['enroll']['date_format'] = 'custom';
$handler->display->display_options['fields']['enroll']['custom_date_format'] = 'd.m.Y H:i';
$handler->display->display_options['fields']['enroll']['second_date_format'] = 'long';
/* Поле: Обработчик испорчен или отсутствует */
$handler->display->display_options['fields']['payment']['id'] = 'order_info';
$handler->display->display_options['fields']['payment']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['payment']['field'] = 'order_info';
/* Критерий фильтра: Платеж: Создатель */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'sl7_order';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['exposed'] = TRUE;
$handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
$handler->display->display_options['filters']['uid']['expose']['label'] = 'Создатель';
$handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
$handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';

/* Display: Управление платежами */
$handler = $view->new_display('page', 'Управление платежами', 'manage_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Управление платежами';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_order any view';
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
$handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
$handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* Поведение при отсутствии результатов: Глобальный: Нефильтруемый текст */
$handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
$handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['empty']['area_text_custom']['content'] = 'Нет платежей для просмотра.';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Платеж: № */
$handler->display->display_options['fields']['oid_1']['id'] = 'oid_1';
$handler->display->display_options['fields']['oid_1']['table'] = 'sl7_order';
$handler->display->display_options['fields']['oid_1']['field'] = 'oid';
$handler->display->display_options['fields']['oid_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['oid_1']['alter']['path'] = 'control-panel/payment/manage/[oid_1]';
$handler->display->display_options['fields']['oid_1']['separator'] = '';
/* Поле: Платеж: Получатель */
$handler->display->display_options['fields']['recipient']['id'] = 'recipient';
$handler->display->display_options['fields']['recipient']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['recipient']['field'] = 'recipient';
$handler->display->display_options['fields']['recipient']['link_to_entity'] = 1;
$handler->display->display_options['fields']['recipient']['view_mode'] = 'full';
$handler->display->display_options['fields']['recipient']['bypass_access'] = 0;
/* Поле: Платеж: Создатель */
$handler->display->display_options['fields']['uid_1']['id'] = 'uid';
$handler->display->display_options['fields']['uid_1']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['uid_1']['field'] = 'uid';
$handler->display->display_options['fields']['uid_1']['link_to_entity'] = 1;
$handler->display->display_options['fields']['uid_1']['view_mode'] = 'full';
$handler->display->display_options['fields']['uid_1']['bypass_access'] = 0;
/* Поле: Платеж: Дата создания */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'sl7_order';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['label'] = 'Создано';
$handler->display->display_options['fields']['created']['date_format'] = 'custom';
$handler->display->display_options['fields']['created']['custom_date_format'] = 'd.m.Y H:i';
$handler->display->display_options['fields']['created']['second_date_format'] = 'long';
/* Поле: Платеж: Состояние */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['link_to_entity'] = 0;
/* Поле: Платеж: Сумма */
$handler->display->display_options['fields']['sum']['id'] = 'sum';
$handler->display->display_options['fields']['sum']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['sum']['field'] = 'sum';
$handler->display->display_options['fields']['sum']['set_precision'] = TRUE;
$handler->display->display_options['fields']['sum']['precision'] = '2';
$handler->display->display_options['fields']['sum']['suffix'] = ' руб.';
$handler->display->display_options['fields']['sum']['link_to_entity'] = 0;
/* Поле: Платеж: Дата зачисления */
$handler->display->display_options['fields']['enroll']['id'] = 'enroll';
$handler->display->display_options['fields']['enroll']['table'] = 'sl7_order';
$handler->display->display_options['fields']['enroll']['field'] = 'enroll';
$handler->display->display_options['fields']['enroll']['date_format'] = 'custom';
$handler->display->display_options['fields']['enroll']['custom_date_format'] = 'd.m.Y H:i';
$handler->display->display_options['fields']['enroll']['second_date_format'] = 'long';
/* Поле: Платеж: Способ оплаты */
$handler->display->display_options['fields']['payment_type']['id'] = 'payment_type';
$handler->display->display_options['fields']['payment_type']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['payment_type']['field'] = 'payment_type';
$handler->display->display_options['fields']['payment_type']['link_to_entity'] = 0;
/* Поле: Платеж: Действия */
$handler->display->display_options['fields']['operations']['id'] = 'operations';
$handler->display->display_options['fields']['operations']['table'] = 'sl7_order';
$handler->display->display_options['fields']['operations']['field'] = 'operations';
$handler->display->display_options['fields']['operations']['label'] = '';
$handler->display->display_options['fields']['operations']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Платеж: № */
$handler->display->display_options['sorts']['oid']['id'] = 'oid';
$handler->display->display_options['sorts']['oid']['table'] = 'sl7_order';
$handler->display->display_options['sorts']['oid']['field'] = 'oid';
$handler->display->display_options['sorts']['oid']['order'] = 'DESC';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Критерий фильтра: Платеж: № */
$handler->display->display_options['filters']['oid']['id'] = 'oid';
$handler->display->display_options['filters']['oid']['table'] = 'sl7_order';
$handler->display->display_options['filters']['oid']['field'] = 'oid';
$handler->display->display_options['filters']['oid']['group'] = 1;
$handler->display->display_options['filters']['oid']['exposed'] = TRUE;
$handler->display->display_options['filters']['oid']['expose']['operator_id'] = 'oid_op';
$handler->display->display_options['filters']['oid']['expose']['label'] = '№';
$handler->display->display_options['filters']['oid']['expose']['operator'] = 'oid_op';
$handler->display->display_options['filters']['oid']['expose']['identifier'] = 'oid';
$handler->display->display_options['filters']['oid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
/* Критерий фильтра: Платеж: Получатель */
$handler->display->display_options['filters']['recipient']['id'] = 'recipient';
$handler->display->display_options['filters']['recipient']['table'] = 'sl7_order';
$handler->display->display_options['filters']['recipient']['field'] = 'recipient';
$handler->display->display_options['filters']['recipient']['group'] = 1;
$handler->display->display_options['filters']['recipient']['exposed'] = TRUE;
$handler->display->display_options['filters']['recipient']['expose']['operator_id'] = 'recipient_op';
$handler->display->display_options['filters']['recipient']['expose']['label'] = 'Получатель';
$handler->display->display_options['filters']['recipient']['expose']['operator'] = 'recipient_op';
$handler->display->display_options['filters']['recipient']['expose']['identifier'] = 'recipient';
$handler->display->display_options['filters']['recipient']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
/* Критерий фильтра: Платеж: Создатель */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'sl7_order';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['group'] = 1;
$handler->display->display_options['filters']['uid']['exposed'] = TRUE;
$handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
$handler->display->display_options['filters']['uid']['expose']['label'] = 'Создатель';
$handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
$handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
$handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
/* Критерий фильтра: Дата: Дата (sl7_order) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'sl7_order';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['group'] = 1;
$handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
$handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Дата';
$handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
$handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
$handler->display->display_options['filters']['date_filter']['year_range'] = '-10:+10';
$handler->display->display_options['filters']['date_filter']['date_fields'] = array(
  'sl7_order.enroll' => 'sl7_order.enroll',
  'sl7_order.created' => 'sl7_order.created',
);
/* Критерий фильтра: Платеж: Состояние */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'sl7_order';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['group'] = 1;
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['label'] = 'Состояние';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
/* Критерий фильтра: Платеж: Способ оплаты */
$handler->display->display_options['filters']['payment_type']['id'] = 'payment_type';
$handler->display->display_options['filters']['payment_type']['table'] = 'sl7_order';
$handler->display->display_options['filters']['payment_type']['field'] = 'payment_type';
$handler->display->display_options['filters']['payment_type']['exposed'] = TRUE;
$handler->display->display_options['filters']['payment_type']['expose']['operator_id'] = 'payment_type_op';
$handler->display->display_options['filters']['payment_type']['expose']['label'] = 'Способ оплаты';
$handler->display->display_options['filters']['payment_type']['expose']['operator'] = 'payment_type_op';
$handler->display->display_options['filters']['payment_type']['expose']['identifier'] = 'payment_type';
$handler->display->display_options['filters']['payment_type']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['payment_type']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['path'] = '-';
$handler->display->display_options['menu']['title'] = 'Управление платежами';
$handler->display->display_options['menu']['description'] = 'Просмотр и управление платежами.';
$handler->display->display_options['menu']['weight'] = '-10';
$handler->display->display_options['menu']['name'] = 'sl7-control-panel';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Личный кабинет */
$handler = $view->new_display('page', 'Личный кабинет', 'user_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Платежи';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_order own view';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* Поведение при отсутствии результатов: Глобальный: Текстовая область */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Нет выставленных счетов';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = '<p>Нет выставленных счетов</p>';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Платеж: № */
$handler->display->display_options['fields']['oid']['id'] = 'oid';
$handler->display->display_options['fields']['oid']['table'] = 'sl7_order';
$handler->display->display_options['fields']['oid']['field'] = 'oid';
$handler->display->display_options['fields']['oid']['separator'] = '';
/* Поле: Платеж: Дата создания */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'sl7_order';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['label'] = 'Создано';
$handler->display->display_options['fields']['created']['date_format'] = 'custom';
$handler->display->display_options['fields']['created']['custom_date_format'] = 'd.m.Y H:i';
$handler->display->display_options['fields']['created']['second_date_format'] = 'long';
/* Поле: Платеж: Состояние */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['link_to_entity'] = 0;
/* Поле: Платеж: Товары */
$handler->display->display_options['fields']['sl7_order_item']['id'] = 'sl7_order_item';
$handler->display->display_options['fields']['sl7_order_item']['table'] = 'field_data_sl7_order_item';
$handler->display->display_options['fields']['sl7_order_item']['field'] = 'sl7_order_item';
$handler->display->display_options['fields']['sl7_order_item']['settings'] = array(
  'link' => 0,
);
$handler->display->display_options['fields']['sl7_order_item']['delta_offset'] = '0';
/* Поле: Платеж: Сумма */
$handler->display->display_options['fields']['sum']['id'] = 'sum';
$handler->display->display_options['fields']['sum']['table'] = 'views_entity_sl7_order';
$handler->display->display_options['fields']['sum']['field'] = 'sum';
$handler->display->display_options['fields']['sum']['set_precision'] = TRUE;
$handler->display->display_options['fields']['sum']['precision'] = '2';
$handler->display->display_options['fields']['sum']['suffix'] = ' руб.';
$handler->display->display_options['fields']['sum']['link_to_entity'] = 0;
/* Поле: Платеж: Оплата счета */
$handler->display->display_options['fields']['pay_link']['id'] = 'pay_link';
$handler->display->display_options['fields']['pay_link']['table'] = 'sl7_order';
$handler->display->display_options['fields']['pay_link']['field'] = 'pay_link';
$handler->display->display_options['fields']['pay_link']['label'] = '';
$handler->display->display_options['fields']['pay_link']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Платеж: № */
$handler->display->display_options['sorts']['oid']['id'] = 'oid';
$handler->display->display_options['sorts']['oid']['table'] = 'sl7_order';
$handler->display->display_options['sorts']['oid']['field'] = 'oid';
$handler->display->display_options['sorts']['oid']['order'] = 'DESC';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Контекстный фильтр: Платеж: Получатель */
$handler->display->display_options['arguments']['recipient']['id'] = 'recipient';
$handler->display->display_options['arguments']['recipient']['table'] = 'sl7_order';
$handler->display->display_options['arguments']['recipient']['field'] = 'recipient';
$handler->display->display_options['arguments']['recipient']['default_action'] = 'default';
$handler->display->display_options['arguments']['recipient']['exception']['title'] = 'Все';
$handler->display->display_options['arguments']['recipient']['default_argument_type'] = 'user';
$handler->display->display_options['arguments']['recipient']['default_argument_options']['user'] = FALSE;
$handler->display->display_options['arguments']['recipient']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['recipient']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['recipient']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Критерий фильтра: Платеж: № */
$handler->display->display_options['filters']['oid']['id'] = 'oid';
$handler->display->display_options['filters']['oid']['table'] = 'sl7_order';
$handler->display->display_options['filters']['oid']['field'] = 'oid';
$handler->display->display_options['filters']['oid']['group'] = 1;
$handler->display->display_options['filters']['oid']['exposed'] = TRUE;
$handler->display->display_options['filters']['oid']['expose']['operator_id'] = 'oid_op';
$handler->display->display_options['filters']['oid']['expose']['label'] = '№';
$handler->display->display_options['filters']['oid']['expose']['operator'] = 'oid_op';
$handler->display->display_options['filters']['oid']['expose']['identifier'] = 'oid';
$handler->display->display_options['filters']['oid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
/* Критерий фильтра: Дата: Дата (sl7_order) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'sl7_order';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['group'] = 1;
$handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
$handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Дата создания';
$handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
$handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
$handler->display->display_options['filters']['date_filter']['year_range'] = '-10:+10';
$handler->display->display_options['filters']['date_filter']['date_fields'] = array(
  'sl7_order.created' => 'sl7_order.created',
);
/* Критерий фильтра: Платеж: Состояние */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'sl7_order';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['group'] = 1;
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['label'] = 'Состояние';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
$handler->display->display_options['path'] = '-';
$handler->display->display_options['menu']['title'] = 'Платежи';
$handler->display->display_options['menu']['description'] = 'Все платежи пользователя.';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['sl7_order'] = array(
  t('Master'),
  t('ещё'),
  t('Применить'),
  t('Сбросить'),
  t('Сортировать по'),
  t('По возрастанию'),
  t('По убыванию'),
  t('Элементов на страницу'),
  t('- Все -'),
  t('Пропустить'),
  t('« первая'),
  t('‹ предыдущая'),
  t('следующая ›'),
  t('последняя »'),
  t('Неисправный обработчик views_entity_sl7_order.oid'),
  t('Создатель'),
  t('Создано'),
  t('Состояние'),
  t('Сумма'),
  t('.'),
  t(','),
  t('Дата зачисления'),
  t('Неисправный обработчик views_entity_sl7_order.order_info'),
  t('Управление платежами'),
  t('Нет платежей для просмотра.'),
  t('№'),
  t('Получатель'),
  t(' руб.'),
  t('Способ оплаты'),
  t('Дата'),
  t('Личный кабинет'),
  t('Платежи'),
  t('Нет выставленных счетов'),
  t('<p>Нет выставленных счетов</p>'),
  t('Товары'),
  t('Все'),
  t('Дата создания'),
);
