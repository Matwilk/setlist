<?php
/**
 * Implements hook_entity_info().
 */
function setlist_entity_info() {

  $info = array();

  $info['musician'] = array(
    'label' => t('Musician'),
    'base table' => 'setlist_musicians',
    'access callback' => 'musician_access_callback',
    'entity keys' => array(
      'id' => 'id',
      'label' => 'name',
    ),
    'entity class' => 'MusicianEntity',
    'controller class' => 'MusicianEntityController',
    'module' => 'setlist',
    'uri callback' => 'entity_class_uri',
    'views controller class' => 'EntityDefaultViewsController',
    'admin ui' => array(
      'path' => 'admin/musicians',
      'controller class' => 'EntityDefaultUIController',
    ),
  );

  $info['instrument'] = array(
    'label' => t('Instrument'),
    'base table' => 'setlist_instruments',
    'access callback' => 'instrument_access_callback',
    'entity keys' => array(
      'id' => 'id',
      'label' => 'name',
    ),
    'entity class' => 'InstrumentEntity',
    'controller class' => 'InstrumentEntityController',
    'module' => 'setlist',
    'uri callback' => 'entity_class_uri',
    'views controller class' => 'EntityDefaultViewsController',
    'admin ui' => array(
      'path' => 'admin/instruments',
      'controller class' => 'EntityDefaultUIController',
    ),
  );

  $info['song'] = array(
    'label' => t('Song'),
    'base table' => 'setlist_songs',
    'entity keys' => array(
      'id' => 'id',
      'label' => 'name',
    ),
    'entity class' => 'SongEntity',
    'controller class' => 'SongEntityController',
    'module' => 'setlist',
    'access callback' => 'song_access_callback',
    'uri callback' => 'entity_class_uri',
    'admin ui' => array(
      'path' => 'admin/songs',
      'controller class' => 'EntityDefaultUIController',
    ),
    'views controller class' => 'EntityDefaultViewsController',
    'fieldable' => TRUE,
    'bundles' => array(
      'song' => array(
        'label' => t('Song'),
        'admin' => array(
          'path' => 'admin/songs',
        ),
      ),
    ),
  );

  return $info;
}

/**
* Implementation of hook_menu().
*/
function setlist_menu() {
  $items['musicians'] = array(
  'title' => 'Musicians',
  'page callback' => 'setlist_musicians',
  'access callback' => TRUE,
  'type' => MENU_NORMAL_ITEM,
  );

  $items['musician/%'] = array(
    'title' => 'Musician',
    'page callback' => 'setlist_view_musician',
    'page arguments' => array(1),
    'access arguments' => array('access content'),
  );

  $items['instruments'] = array(
  'title' => 'Instruments',
  'page callback' => 'setlist_instruments',
  'access callback' => TRUE,
  'type' => MENU_NORMAL_ITEM,
  );

  $items['instruments/%'] = array(
    'title' => 'Instruments',
    'page callback' => 'setlist_view_instrument',
    'page arguments' => array(1),
    'access arguments' => array('access content'),
  );
      
  $items['songs'] = array(
  'title' => 'Songs',
  'page callback' => 'setlist_songs',
  'access callback' => TRUE,
  'type' => MENU_NORMAL_ITEM,
  );

  $items['song/%'] = array(
    'title' => 'Song',
    'page callback' => 'setlist_view_song',
    'page arguments' => array(1),
    'access arguments' => array('access content'),
  );

  return $items;
}

/**
* Musicians callback.
*/
function setlist_musicians() {
  $musicians = entity_load('musician', array(1));

  if (!isset($musicians[1])) {
    $entity = entity_create('musician', array('id' => 1));
    $entity->name = t('Marcus');
    $entity->save();
    return 'Blah';
  }
  else {  
    $list = entity_view('musician', $musicians);
  
    $output = array();

    foreach ($list['musician'] as $musician) {
      $output[] = drupal_render($musician);
    }
  }

  dpm($output);

  return implode($output);
}

/**
* Instruments callback.
*/
function setlist_instruments() {
  $instruments = entity_load('instrument', array(1));

  $list = entity_view('instrument', $instruments);

  $output = array();

  foreach ($list['instrument'] as $instrument) {
    $output[] = drupal_render($instrument);
  }

  dpm($output);

  return implode($output);
}

/**
* Songs callback.
*/
function setlist_songs() {
  $songs = entity_load('song', array(1));

  if (!isset($songs[1])) {
    $entity = entity_create('song', array('id' => 1));
    $entity->name = t('Durangs Hornpipe');
    $entity->genre = t('Folk');
    $entity->year = 1900;
    $entity->save();
    return 'Blah';
  }
  else {    
    $list = entity_view('song', $songs);
  
    $output = array();

    foreach ($list['song'] as $song) {
      $output[] = drupal_render($song);
    }

    dpm($output);

    return implode($output);
  }
}

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
 * Callback function for displaying the individual song page
 */
function setlist_view_song($id) {

  $songs = entity_load('song', array($id));
  dpm($songs);
  $song = $songs[$id];

  drupal_set_title($song->name);
  $output = entity_view('song', array($song));
  
  return $output;
}

/**
 * Callback function for displaying the individual musician page
 */
function setlist_view_musician($id) {

  $musicians = entity_load('musician', array($id));
  $musician = $musicians[$id];

  drupal_set_title($musician->name);
  $output = entity_view('musician', array($musician));
  
  return $output;

}

/**
 * Callback function for displaying the individual instrument page
 */
function setlist_view_instrument($id) {

  $instruments = entity_load('instrument', array($id));
  $instrument = $instruments[$id];

  drupal_set_title($instrument->name);
  $output = entity_view('instrument', array($instrument));
  
  return $output;

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

/**
 * Form definition for adding / editing a song.
 */
function song_form($form, &$form_state, $song = NULL) {

  $form['name'] = array(
    '#title' => t('Song name'),
    '#type' => 'textfield',
    '#default_value' => isset($song->name) ? $song->name : '',
    '#required' => TRUE,
  );

  $form['genre'] = array(
    '#title' => t('Song genre'),
    '#type' => 'textfield',
    '#default_value' => isset($song->genre) ? $song->genre : '',
    '#required' => TRUE,
  );

  $form['year'] = array(
    '#title' => t('Song year'),
    '#type' => 'textfield',
    '#default_value' => isset($song->year) ? $song->year : '',
    '#required' => TRUE,
  );  
  
  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => isset($song->id) ? t('Update song') : t('Save song'),
    '#weight' => 50,
  );

  field_attach_form('song', $song, $form, $form_state);

  return $form;
}

function _song_form_validate(&$form, &$form_state) {
  drupal_set_message('hi from validation');
    
  dpm($form);
  dpm($form_state);
}

/**
 * Submit handler for the song add/edit form.
 */
function song_form_submit($form, &$form_state) {
  $song = entity_ui_form_submit_build_entity($form, $form_state);
  $song->save();
  drupal_set_message(t('The song: @name has been saved.', array('@name' => $song->name)));
  $form_state['redirect'] = 'admin/songs';
}

/**
 * Form definition for adding / editing a musician.
 */
function musician_form($form, &$form_state, $musician = NULL) {

  $form['name'] = array(
    '#title' => t('Musician name'),
    '#type' => 'textfield',
    '#default_value' => isset($musician->name) ? $musician->name : '',
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => isset($musician->id) ? t('Update musician') : t('Save musician'),
    '#weight' => 50,
  );

  field_attach_form('musician', $musician, $form, $form_state);

  return $form;
}

/**
 * Submit handler for the musician add/edit form.
 */
function musician_form_submit($form, &$form_state) {
  $musician = entity_ui_form_submit_build_entity($form, $form_state);
  $musician->save();
  drupal_set_message(t('The musician: @name has been saved.', array('@name' => $musician->name)));
  $form_state['redirect'] = 'admin/musicians';
}

/**
 * Form definition for adding / editing a instrument.
 */
function instrument_form($form, &$form_state, $instrument = NULL) {

  $form['name'] = array(
    '#title' => t('Instrument name'),
    '#type' => 'textfield',
    '#default_value' => isset($instrument->name) ? $instrument->name : '',
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => isset($instrument->id) ? t('Update instrument') : t('Save instrument'),
    '#weight' => 50,
  );

  field_attach_form('instrument', $instrument, $form, $form_state);

  return $form;
}

/**
 * Submit handler for the musician add/edit form.
 */
function instrument_form_submit($form, &$form_state) {
  $instrument = entity_ui_form_submit_build_entity($form, $form_state);
  $instrument->save();
  drupal_set_message(t('The instrument: @name has been saved.', array('@name' => $instrument->name)));
  $form_state['redirect'] = 'admin/instruments';
}

/**
 * Implements hook_field_info().
 */
function setlist_field_info() { 
  
  return array(
    'setlist_player' => array(
      'label' => t('Player'),
      'description' => t('Custom Player Field'),
      'default_widget' => 'setlist_player_widget',
      'default_formatter' => 'setlist_player_formatter', 
    ),
  ); 
}

/**
 * Implements hook_field_widget_info().
 */
function setlist_field_widget_info() { 
  return array(
    'setlist_player_widget' => array(
      'label' => t('Default'),
      'field types' => array(
        'setlist_player'
      ),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT, 
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ), 
    ), 
  ); 
}

/**
 * Implements hook_field_widget_form().
 */
function setlist_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  /// \todo pull out existing values from form_state 

  $element += array(
    '#type' => 'fieldset', 
  );

  $required = $element['#required']; 
  $item =& $items[$delta];   

  $musicians = entity_load('musician', FALSE, NULL, TRUE);
  $musician_names = array('');
  foreach ($musicians as $key => $musician) {
    array_push($musician_names, $musician->name);
  }
  
  $element['musician'] = array( 
    '#title' => t('Musician'), 
    '#type' => 'textfield', 
    '#required' => $required, 
    '#attributes' => array('disabled' => 'disabled'),
    '#default_value' => isset($item['musician']) ? $item['musician'] : $musician_names[$delta], ); 

  $instruments = entity_load('instrument', FALSE, NULL, TRUE);
  $instrument_names = array('');
  
  foreach ($instruments as $key => $instrument) {
    array_push($instrument_names, $instrument->name);
  }
    
  $element['instrument'] = array( 
    '#title' => t('Instrument'), 
    '#type' => 'select', 
    '#required' => $required, 
    '#options' => $instrument_names,
    '#default_value' => isset($item['instrument']) ? $item['instrument'] : '', ); 
      
  return $element;
}

/**
 * Implements hook_field_is_empty().
 */
function setlist_field_is_empty($item, $field) { 
  $has_stuff = FALSE; 
   
  // has the user entered a musician and instrument? 
  if (!empty($item['musician']) && (!empty($item['instrument']))) { 
    $has_stuff = TRUE; 
  } 
  return !$has_stuff; 
}

/**
 * Implements hook_field_validate()
 */
function setlist_player_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) { 
  dpm($items);
  foreach ($items as $delta => $item) {
    dpm($item);
  }
}

function setlist_form_alter(&$form, &$form_state, $form_id)
{  
  if ($form_id == "song_form") {
    $form['#validate'][] = '_song_form_validate';
    dpm($form);
    dpm($form_state);
    dpm($form['field_player']);
    $delta = $form_state['field']['field_player']['und']['items_count'];
    $lang = $form['field_player']['#language'];
    
    if ($delta < 1) {
      dpm('Blah');

      $player_field = $form['field_player'];  
      $fieldUnd = $player_field[$lang][0];
      
      $musicians = entity_load('musician', FALSE, NULL, TRUE);
      $count = 0;
      foreach ($musicians as $key => $musician) {
        if ($count == 0) {
          $form['field_player'][$lang][0]['musician']['#title'] = $musician->name;
          $form['field_player'][$lang][0]['musician']['#default_value'] = $musician->name;
        }
        else {
          $fieldUnd['musician']['#title'] = $musician->name;
          $fieldUnd['musician']['#default_value'] = $musician->name;
          array_push($form['field_player'][$lang], $fieldUnd);
        }
        
        dpm($count);
        $count++;
      }

      dpm($fieldUnd);      
      dpm($form);
    }
    
    $form['field_player'][$lang]['add_more']['#access'] = FALSE;
  }
}
