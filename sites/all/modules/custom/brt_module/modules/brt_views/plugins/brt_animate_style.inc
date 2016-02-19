<?php
/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class BrtViewsAnimateStyle extends views_plugin_style {
  /**
   * Definition.
   */
  function option_definition() {
    $options = parent::option_definition();
    drupal_add_library('system', 'ui.sortable');
    $options['animate'] = array('default' => '');
    $options['animate_all'] = array('default' => TRUE);
    $options['use_animate'] = array('default' => TRUE);
    $options['delay_time'] = array('default' => '0.4');
    $options['delay_step'] = array('default' => '0.2');
    $options['add_class'] = '';
    return $options;
  }

  /**
   * Form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $option_animate = array(
      '' => 'None',
      'Attention Seekers'  =>  array(
    	 "bounce" => "bounce",
    	 "flash" => "flash",
    	 "pulse" => "pulse",
    	 "rubberBand" => "rubberBand",
    	 "shake" => "shake",
    	 "swing" => "swing",
    	 "tada" => "tada",
    	 "wobble" => "wobble",
      ),
      'Bouncing Entrances'  =>  array(
        "bounceInDown"  =>  "​bounceInDown​",
        "bounceIn" => "​bounceIn​",
        "bounceInLeft" => "​bounceInLeft​",
        "bounceInUp" => "​bounceInUp​",
        "bounceInRight" => "​bounceInRight​"
      ),
      'Fading Entrances'  =>  array(
      	"fadeIn" => "fadeIn",
      	"fadeInDown" => "fadeInDown",
      	"fadeInDownBig" => "fadeInDownBig",
      	"fadeInLeft" => "fadeInLeft",
      	"fadeInLeftBig" => "fadeInLeftBig",
      	"fadeInRight" => "fadeInRight",
      	"fadeInRightBig" => "fadeInRightBig",
      	"fadeInUp" => "fadeInUp",
      	"fadeInUpBig" => "fadeInUpBig",
      ),
      'Flippers'  =>  array(
      	"flip" => "flip",
      	"flipInX" => "flipInX",
      	"flipInY" => "flipInY",
      ),
      'Lightspeed'  =>  array(
        "lightSpeedIn" => "lightSpeedIn",
    	   "lightSpeedOut" => "lightSpeedOut",
      ),
      'Rotating Entrances'  =>  array(
      	"rotateIn" => "rotateIn",
      	"rotateInDownLeft" => "rotateInDownLeft",
      	"rotateInDownRight" => "rotateInDownRight",
      	"rotateInUpLeft" => "rotateInUpLeft",
      	"rotateInUpRight" => "rotateInUpRight",
      ),
      'Sliders'  =>  array(
      	"slideInDown" => "slideInDown",
      	"slideInLeft" => "slideInLeft",
      	"slideInRight" => "slideInRight",
      ),
      'Specials' => array(
        "rollIn" => 'rollIn',
      ),
    );
    $content_inner = '';
    if($this->options['input_animate']){
      $animate_class = $this->options['input_animate'];
      $animate_class = explode('|',$animate_class);
      $animate_class = array_filter($animate_class);
      foreach($animate_class as $key => $value){
        $content_inner .= '<li><span class="animate-value">'.$value.'<i>|</i></span><span class="delete-animate"></span></li>';
      }
    }
    $content = '<ul id="sortable">'.$content_inner.'</ul>';
    $form['#attached']['js'] = array(
      drupal_get_path('module', 'brt_views') . '/js/brt_views.js',
    );
    $form['#attached']['css'] = array(
      drupal_get_path('module', 'brt_views') . '/css/brt_views.css',
    );

    /*$form['social_types'] = array(
        '#type'         => 'select',
        '#options'      => array(
            'tt-metro-social'   => 'Metro',
            'circular'          => 'Circular'
        ),
        '#default_value'        => $this->options['social_types'],
        '#description'          => t('This options currently working in MD Official Theme')
    );*/
    $form['add_class'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom class'),
      '#default_value' => $this->options['add_class'],
      '#description' => 'The class to provide on each row.',
    );
    $form['use_animate'] = array(
      '#type' =>'checkbox',
      '#default_value' => $this->options['use_animate'],
      '#title' => t('Use animation for row content.'),
    );
    $form['animate_all'] = array(
      '#type' =>'checkbox',
      '#default_value' => $this->options['animate_all'],
      '#title' => t('Use One animation for all row.'),
      '#description' => t('Random in your value select'),
    );
    $form['delay_time'] = array(
      '#type' => 'textfield',
      '#title' => t('Delay before the animation starts'),
      '#default_value' => $this->options['delay_time'],
      '#description' => 'Ex: 0.4 or 1. Time delay is sec',
      '#attributes' => array('class' => array('animate-delay-time')),
    );
    $form['delay_step'] = array(
      '#type' => 'textfield',
      '#title' => t('Time Step Delay'),
      '#default_value' => $this->options['delay_step'],
      '#description' => 'Ex: 0.4 or 1. Time step is sec',
      '#attributes' => array('class' => array('animate-delay-time')),
    );

    $form['wrap_sort'] = array(
        '#type' => 'container',
        '#prefix' => '<div class="wrap-sort">',
        '#suffix' => '</div>',
    );
    $form['wrap_sort']['animate'] = array(
      '#type' => 'select',
      '#title' => t('Select Animation'),
      '#default_value' => $this->options['animate'],
      '#options' => $option_animate,
      '#attributes' => array('class' => array('animate-select')),
      '#multiple' => TRUE,
      '#required' => TRUE,
    );
    $form['wrap_sort']['button_animate'] = array(
       '#markup' => '<div class="wrap-add-click"><input type="button" value="add" class="form-submit add-click" /></div>',
    );
    $form['wrap_sort']['sort_animate'] = array(
      '#title' => t('Sort Animate'),
      '#type' => 'container',
      '#prefix' => '<h3>Sort Animate</h3><div class="sort-animate">',
      '#suffix' => '</div>',
      'content' => array(
        '#type' => 'markup',
        '#markup' => $content,
        '#weight' => 0,
      ),
    );
    $form['input_animate'] = array(
      '#title' => t('Animate Value'),
      '#type' => 'hidden',
      '#default_value' => $this->options['input_animate'],
      '#attributes' => array('class' => array('animate-value-hidden')),
    );
  }
  /**
   * Validate the options form.
   */
   function options_validate(&$form, &$form_state) {
   }
  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
   //function options_submit(&$form, &$form_state) {
//      //dpm($form_state);
//   }
}
