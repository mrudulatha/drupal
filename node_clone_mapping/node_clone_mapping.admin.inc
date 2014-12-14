<?php

/**
 * @file
 * Administration pages for mapping cloned content.
 */

/**
 * Function to build administration page for node clone mapping.
 */
function node_clone_mapping_administration_form() {
  $form = array();
  $content_types = node_type_get_types();
  foreach ($content_types as $type) {
    $node_types[$type->type] = $type->name;
  }

  $form['clone_mapping_content_type'] = array(
    '#title' => t('Node Types'),
    '#description' => t('Choose the node types to enable mapping when node clone.'),
    '#type' => 'checkboxes',
    '#options' => $node_types,
    '#default_value' => variable_get('clone_mapping_content_type', array()),
    '#required' => TRUE,
  );
  $form['copy_mapping_comments'] = array(
    '#title' => t('Copy Comments on clone'),
    '#description' => t('Enable this option to copy comments for the selected node types.'),
    '#type' => 'radios',
    '#options' => array(1 => t('Yes'), 0 => t('No')),
    '#default_value' => variable_get('copy_mapping_comments', ''),
    '#required' => TRUE,
  );
  $form['copy_mapping_comments_hierarchy'] = array(
    '#title' => t('Copy Comments through clone hierarchy'),
    '#description' => t('Enable this option to copy comments through the clone hierarchy.'),
    '#type' => 'checkbox',
    '#states' => array(
      'invisible' => array(
        ':input[name="copy_mapping_comments"]' => array('value' => 0),
      ),
      'disabled' => array(
        ':input[name="copy_mapping_comments"]' => array('value' => 0),
      ),
    ),
    '#default_value' => variable_get('copy_mapping_comments_hierarchy', ''),
  );
  return system_settings_form($form);
}
