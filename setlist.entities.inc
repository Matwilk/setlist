<?php

/**
 * Access callback for song entities.
 */
function song_access_callback($op, $song = NULL, $account = NULL) {
  if ($op == 'view' || $op == 'update' || $op == 'create' || $op == 'delete') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Access callback for musician entities.
 */
function musician_access_callback($op, $musician = NULL, $account = NULL) {
  if ($op == 'view' || $op == 'update' || $op == 'create' || $op == 'delete') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Access callback for instrument entities.
 */
function instrument_access_callback($op, $instrument = NULL, $account = NULL) {
  if ($op == 'view' || $op == 'update' || $op == 'create' || $op == 'delete') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Extending the EntityAPIController for the Musician entity.
 */
class MusicianEntityController extends EntityAPIController {

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {

    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    // Our additions to the $build render array

    return $build;
  }
}

/**
 * Extending the EntityAPIController for the Instrument entity.
 */
class InstrumentEntityController extends EntityAPIController {

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {

    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    // Our additions to the $build render array

    return $build;
  }
}

/**
 * Extending the EntityAPIController for the Song entity.
 */
class SongEntityController extends EntityAPIController {

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {

    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    dpm($entity);
    
    // Our additions to the $build render array
    $build['genre'] = array(
      '#type' => 'markup',
      '#markup' => check_plain($entity->genre),
      '#prefix' => '<div class="song-genre">',
      '#suffix' => '</div>',
    );
    $build['year'] = array(
      '#type' => 'markup',
      '#markup' => check_plain($entity->year),
      '#prefix' => '<p>Year: ',
      '#suffix' => '</p>',
    );

    return $build;
  }
}

/**
 * Song entity class extending the Entity class
 */
class SongEntity extends Entity {

  /**
   * Change the default URI from default/id to song/id
   */
  protected function defaultUri() {
    return array('path' => 'song/' . $this->identifier());
  }
}

/**
 * Musician entity class extending the Entity class
 */
class MusicianEntity extends Entity {

  /**
   * Change the default URI from default/id to musician/id
   */
  protected function defaultUri() {
    return array('path' => 'musician/' . $this->identifier());
  }
}

/**
 * Instrument entity class extending the Entity class
 */
class InstrumentEntity extends Entity {

  /**
   * Change the default URI from default/id to instrument/id
   */
  protected function defaultUri() {
    return array('path' => 'instrument/' . $this->identifier());
  }
}

