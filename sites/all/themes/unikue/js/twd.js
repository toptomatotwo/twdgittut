 jQuery(document).ready(function() {

  /* window size monitor */
  jQuery.windowWidth = jQuery(window).width();
	jQuery.windowHeight = jQuery(window).height();
	jQuery('#widthMonitor').html(jQuery.windowWidth);  //same logic that you use in the resize...

  jQuery(window).resize(function() {
  jQuery.windowWidth = jQuery(window).width();
	jQuery.windowHeight = jQuery(window).height();
	jQuery('#widthMonitor').html(jQuery.windowWidth);
                      });
})