(function($){
    $(document).ready(function() {
        // Flickr, find your id from idgettr.com
        if ($(".flick-content").size() > 0) {
            var flickr = Drupal.settings.flickr;
            $('.flick-content').jflickrfeed({
                limit: flickr.flickrNum,
                qstrings: {
                    id: flickr.flickrID
                },
                itemTemplate: '<div class="flickr_badge_image">' +
                    '<a href="{{image_b}}" data-gal="lightbox[flickr]"><img src="{{image_s}}" alt="{{title}}" /><span class="hover"></span></a>' +
                    '</div>',
                itemCallback: function (data) {
                    /*if ($("a[data-gal^='lightbox']")[0]) {
                        $("a[data-gal^='lightbox']").prettyPhoto({
                            animation_speed: 'normal',
                            theme: 'dark_rounded',
                            autoplay_slideshow: false,
                            overlay_gallery: false,
                            show_title: false
                        });
                    }*/
                }
            });
        }
    })
})(jQuery);