<?php

/**
 * @file
 * Common functions used for node clone mapping.
 */

/**
 * Prepares a comment to be copied.
 */
function _node_clone_mapping_comment_copy($nid, $cid) {
  global $user;
  $comment = comment_load($cid, $reset = TRUE);
  $comment->cid = NULL;
  $comment->nid = $nid;
  $comment->is_anonymous = FALSE;
  comment_submit($comment);
  comment_save($comment);
}

/**
 * Function to get the parent nodes of nodes which got cloned.
 */
function _node_clone_mapping_get_clone_parent_mapping($cnid, &$node_clone_mapping) {
  $result = db_select('node_clone_map', 'ncm')->fields('ncm', array('pnid'))->condition('ncm.cnid', $cnid, '=')->execute();
  foreach ($result as $record) {
    $pnid = $record->pnid;
    if (!empty($pnid) && $pnid > 0) {
      array_push($node_clone_mapping, $pnid);
      _node_clone_mapping_get_clone_parent_mapping($pnid, $node_clone_mapping);
    }
  }
}

/**
 * Function to get the child nodes of a node being cloned.
 */
function _node_clone_mapping_get_clone_child_mapping($pnid, &$node_clone_mapping) {
  $cnid = '';
  $result = db_select('node_clone_map', 'ncm')->fields('ncm', array('cnid'))->condition('ncm.pnid', $pnid, '=')->execute();
  foreach ($result as $record) {
    $cnid = $record->cnid;
    if (!empty($cnid) && $cnid > 0) {
      array_push($node_clone_mapping, $cnid);
      _node_clone_mapping_get_clone_child_mapping($cnid, $node_clone_mapping);
    }
  }
}

/**
 * Copies newly created comment for the cloned chain.
 */
function _node_clone_mapping_copy_comments($comment) {
  $node_clone_parent_map = array();
  $node_clone_child_map = array();
  _node_clone_mapping_get_clone_parent_mapping($comment->nid, $node_clone_parent_map);
  _node_clone_mapping_get_clone_child_mapping($comment->nid, $node_clone_child_map);

  $node_clone_map = array_merge($node_clone_parent_map, $node_clone_child_map);

  if (!empty($node_clone_map) && is_array($node_clone_map)) {
    foreach ($node_clone_map as $nid) {
      $comment->cid = NULL;
      $comment->nid = $nid;
      $comment->is_anonymous = FALSE;
      comment_submit($comment);
      comment_save($comment);
    }
  }
}
