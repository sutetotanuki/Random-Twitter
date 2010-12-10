<?php

function twitter_random_admin_settings() {
  $form['twitter_random_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node Types'),
    '#options' => node_get_types('names'),
    '#default_value' => variable_get('twitter_random_types', array('story' => 'story', 'blog' => 'blog')),
  );
  
  $form['twitter_random_post_format'] = array(
    '#type' => 'textfield',
    '#title' => 'フォーマット',
    '#maxlength' => 140,
    '#description' => '!url, !url-alias, !tinyurl, !title, and !user ←こんなの使えます',
    '#default_value' => variable_get('twitter_random_post_format', 'New post: !title !tinyurl'),
  );
  $form['twitter_random_interval'] = array(
    '#type' => 'textfield',
    '#title' => 'つぶやき間隔',
    '#maxlength' => 2,
    '#description' => 'つぶやきの間隔を1-99時間の間で指定してください。',
    '#default_value' => variable_get('twitter_random_interval', 24),
  );
  $form['twitter_random_on'] = array(
    '#type' => 'checkbox',
    '#title' => 'ランダムでつぶやく？',
    '#default_value' => variable_get('twitter_random_on', FALSE),
  );
  $form['twitter_random_account'] = array(
    '#type' => 'select',
    '#title' => 'どのアカウントでつぶやく？',
    '#options' => twitter_random_account_options(),
    '#default_value' => variable_get('twitter_random_account', ''),
  );
  
  return system_settings_form($form);
}

function twitter_random_admin_settings_validate($form, $form_state) {
  $interval = $form_state['values']['twitter_random_interval'];
  
  if (!is_numeric($interval)) {
    form_set_error('twitter_random_interval', '数字でお願いします。');
  }
  if ($interval < 1) {
    form_set_error('twitter_random_interval', '1以上で！');
  }
}

function twitter_random_account_options($account = NULL) {
  if (empty($account)) {
    global $user;
    $account = $user;
  }

  $twitter_accounts = twitter_get_user_accounts($account->uid);
  $options = array();
  // 空白を許可
  $options[''] = '';
  foreach ($twitter_accounts as $twitter_account) {
    $options[$twitter_account->id] = $twitter_account->screen_name;
  }
  
  return $options;
}
