(function($){
    $(function(){

    });
    $(window).load(function(){
        $('.menu').addClass('w-nav-menu nav');
        $('.menu li a').addClass('w-nav-link nav-link');

    });
    $(document).ready(function(){
        WebFont.load({
            google: {
                families: ["Open Sans:300,300italic,400,400italic,600,600italic,700,700italic,800,800italic"]
            }
        });

        $('a[href^=https][href*=facebook]').addClass('fb');
        $('a[href^=https][href*=twitter]').addClass('twitter');
        $('a[href^=https][href*=linked]').addClass('linkedin');
        $('a[href^=https][href*=mail]').addClass('emial');
        $('a[href^=https][href*=google]').addClass('gplus');

        $('.view-features-style-1 .views-row-even .w-col-5').addClass('w-col-push-7 mt-mb');
        $('.view-features-style-1 .views-row-even .w-col-7').addClass('w-col-pull-5');
        $('.view-features-style-1 .views-row-even .w-col-5').removeClass('col');
        $('.view-features-style-1 .divder:last').hide();
        $('.view-services .divder:last').hide();
    });


    $(document).scroll(function () { "use strict";
        var y = $(this).scrollTop();
        if (y >= 300) {
            $('.dot-container').fadeIn();
        } else {
            $('.dot-container').fadeOut();
        }
    });
    $(window).load(function () {
        "use strict";
        $('.loading').fadeOut();
        $('.timer').countTo();
    });

})(jQuery);
