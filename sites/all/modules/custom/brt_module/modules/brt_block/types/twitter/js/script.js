jQuery(document).ready(function($) {
    var twitter_account = Drupal.settings.twitter_account;
    var twitter_max = Drupal.settings.twitter_num;
    var tck = Drupal.settings.tck;
    var tcs = Drupal.settings.tcs;
    var tat = Drupal.settings.tat;
    var tats = Drupal.settings.tats;
    $(".twitter-widget").tweet({
        modpath: location.href.substring(0,location.href.lastIndexOf("/")+1) + "?q=tweet&tck="+tck+"&tcs="+tcs+"&tat="+tat+"&tats="+tats,
        count: twitter_max,
        username: twitter_account,
        template: '{text}{time}'
    });
});