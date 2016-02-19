;(function($){
    $(document).ready(function(){
        var bgSettings = Drupal.settings.bgSettings;
        console.log(bgSettings);
        if(bgSettings[0] != null) {
            $("#hero").multiBackground(bgSettings,false);
        }
       // $("#hero").multiBackground([{"type":"vimeo","attachment":"parallax","id":"114758996","video":{"muted":false}}], false);;

    });
})(jQuery);