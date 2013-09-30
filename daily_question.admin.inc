<?php

/*
 * Configure Daily Question settings.
 */
function daily_question_form($form, &$form_state, $question = NULL) {
  $form['question_date'] = array(
    '#type' => 'date',
    '#title' => t('Question date'),
    '#description' => t("The date on which this question should appear."),
    '#default_value' => isset($question->question_date) ? $question->question_date : '',
  );
  $form['question_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Question text.'),
    '#default_value' => isset($question->question_text) ? check_plain($question->question_text) : '',
  );
  // Basic campaign information
  $form['answers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Possible Answers'),
  );
  $form['answers']['answer_1'] = array(
    '#type' => 'textfield',
    '#title' => t('Answer 1'),
    '#description' => t('The first multiple-choice answer for this question.'),
    '#default_value' => isset($question->answer_1) ? check_plain($question->answer_1) : '',
  );
  $form['answers']['answer_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Answer 2'),
    '#description' => t('The second multiple-choice answer for this question.'),
    '#default_value' => isset($question->answer_2) ? check_plain($question->answer_2) : '',
  );
  $form['answers']['answer_3'] = array(
    '#type' => 'textfield',
    '#title' => t('Answer 3'),
    '#description' => t('The third multiple-choice answer for this question.'),
    '#default_value' => isset($question->answer_3) ? check_plain($question->answer_3) : '',
  );
  $form['read_more'] = array(
    '#type' => 'textfield',
    '#title' => t('Read More.'),
    '#description' => t('URL for more information on Daily Question answers.'),
    '#default_value' => isset($question->read_more) ? check_plain($question->read_more) : '',
  );
  $form['correct_answers'] = array(
    '#markup' => get_correct_answers(),
    '#title' => t('Correct Answers'),
    '#description' => t('The list of users who answered this question correctly.'),
  );
  $form['incorrect_answers'] = array(
    '#markup' => get_incorrect_answers(),
    '#title' => t('Incorrect Answers'),
    '#description' => t('The list of users who answered this question incorrectly.'),
  );

  field_attach_form('campaign', $question, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($question->id) ? t('Update Question') : t('Save Question'),
    ),
  );
  return $form;
}

function get_correct_answers() {
  $output = t('<b>Correct Answers</b>');
  $items['items'] = array(
    l('Mike', 'user/1'),
    l('John', 'user/1'),
  );
  $output .= theme('item_list', $items);
  $output .= t('<br />');
  return $output;
}

function get_incorrect_answers() {
  $output = t('<b>Inorrect Answers</b>');
  $items['items'] = array(
    l('Joe', 'user/1'),
    l('Sally', 'user/1'),
  );
  $output .= theme('item_list', $items);
  $output .= t('<br />');
  return $output;
}

/*
 * Submit function for Daily Questions.
 */
function daily_question_form_submit($form, &$form_state) {

  $question = entity_ui_form_submit_build_entity($form, $form_state);
  $question->save();
  drupal_set_message(t('The question has been saved'));
  $form_state['redirect'] = 'admin/daily-question';

}
