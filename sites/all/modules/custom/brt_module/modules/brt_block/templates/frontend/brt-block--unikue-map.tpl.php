
<div class="map-section"><!-- locate us on map now div -->
  	<div class="w-container">
	    <div class="w-row">
		    <div class="w-col w-col-4 hero-column">
		        <div class="line-hero map"></div>
		        <div class="line-hero map"></div>
		    </div>
		    <div class="w-col w-col-4 hero-column">
		    <a class="button location" href="#map" data-ix="hide-and-show"><?php print $brt_block['show_map_button_text'];?></a>
		    </div>
		    <div class="w-col w-col-4">
		        <div class="line-hero map"></div>
		        <div class="line-hero map"></div>
		    </div>
	    </div>
  	</div>
</div>
<div class="map-wrapper" data-ix="new-interaction">
  <div class="w-widget w-widget-map" data-widget-latlng="<?php print $brt_block['map_latlng'];?>" data-widget-style="<?php print $brt_block['map_type'];?>" data-widget-zoom="<?php print $brt_block['map_zoom'];?>"></div>
</div><!-- end locate us on map now div -->