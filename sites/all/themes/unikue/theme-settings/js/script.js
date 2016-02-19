(function($){
    $(window).load(function(){


    })
    $(document).ready(function(){
        //===== Form elements styling =====//
        $("select:not('.form-select-icon'), input:checkbox, input:radio, input:file, input:text, textarea").uniform();

        //===== Collapsible elements management =====//

        $('.exp').collapsible({
            defaultOpen: 'current',
            cookieName: 'navAct',
            cssOpen: 'active-collapsible',
            cssClose: 'inactive-collapsible',
            speed: 200
        });

        $('.opened').collapsible({
            defaultOpen: 'opened,toggleOpened',
            cssOpen: 'inactive',
            cssClose: 'normal',
            speed: 200
        });

        $('.closed').collapsible({
            defaultOpen: '',
            cssOpen: 'inactive',
            cssClose: 'normal',
            speed: 200
        });


        $('.goTo').collapsible({
            defaultOpen: 'openedDrop',
            cookieName: 'smallNavAct',
            cssOpen: 'active',
            cssClose: 'inactive',
            speed: 100
        });
/////////////////////////////////////////////// SHOW/HIDE TABS ////////////////////////////////////////////////////////
        var tabCookieName = "maintabs";
        var subTab1CookieName = "subtabs1";
        $(function() {
            // Save cookie for each tab group, each tab group need unique cookie name
            if($.cookie != undefined) {
                $("#main-settings").tabs({tabs: 'a.main-tab', active : ($.cookie(tabCookieName) || 0),
                    activate : function( event, ui ) {
                        var newIndex = ui.newTab.parent().children().index(ui.newTab);
                        $.cookie(tabCookieName, newIndex, { expires: 1 });
                    }});
            }
        });
        if($(".main-tab").length) {
            $(document).delegate(".main-tab",'click',function(event) {
                event.preventDefault();
                var current = $(this).attr("href");
                $("#menu a.main-tab.active-collapsible").each(function(){
                    if($(this).attr("href") != current) {
                        $(this).collapsible('close');
                    }
                });
            });
        }

/////////////////////////////////////////////// Sub tab scrolling ////////////////////////////////////////////////

        $('.nested-tab .sub-tab').click(function(event) {
            event.preventDefault();
            var $anchor = $(this);
            $('html, body').animate({
                scrollTop : $($anchor.attr('href')).offset().top - 70
            });
        });

/////////////////////////////////////////////// JQUERY UI SlIDER RANGE /////////////////////////////////////////////////
        $(".slider-range").each(function(){
            var $self = $(this),
                id = $(this).attr('id'),
                max = $(this).data('max'),
                min = $(this).data('min'),
                defaultValue = $(this).data('value');
            console.log(defaultValue);
            // Append an element to make it slider range
            $(this).parents(".form-item").append("<div id='"+id+"-slider-range'></div>");
            // Call jquery slider ui
            if($("#"+id+"-slider-range").size() > 0) {
                $("#"+id+"-slider-range").slider({
                    range: "min",
                    value: defaultValue,
                    min: min,
                    max: max,
                    slide: function( event, ui ) {
                        $self.val( ui.value );
                        $self[0].setAttribute("value", ui.value );
                    }
                });
            }

            // Put value of slider range into input
            $self.val(defaultValue);
        });
/////////////////////////////////////////////// UniForm ///////////////////////////////////////////////
        $(".formFont select").uniform();

//////////////////////////////////////////////////// Color Picker /////////////////////////////////////////////////////
        $(".form-colorpicker").spectrum({
            showAlpha: true,
            showInput: true,
            allowEmpty:true,
            showInitial: true,
            preferredFormat: "hex3"
        })
//////////////////////////////////////////////////// Add Class To Default Submit /////////////////////////////////////////////////////
        $("#submit-footer .form-actions #edit-submit").addClass("btn btn-save");
        /* Display on/off remove button */

        /* Check left menu scrolling over itself and set fixed position */
        var leftOffset = $("#leftSide").offset().top;
        $(window).scroll(function(){

            var windowScrollTop = $(window).scrollTop();

            if($(window).scrollTop() >= leftOffset) {
                if($("body").hasClass('toolbar-drawer')) {
                    $("#leftSide").css({position: 'fixed',top: '66px' ,left: 0});
                } else {
                    $("#leftSide").css({position: 'fixed',top: '31px' ,left: 0});
                }

                $("#rightSide").css({'margin-left':'21%'});
            } else {
                $("#leftSide").css({position: 'static'});
                $("#rightSide").css({'margin-left': 0});
            }
        });



        // Hide Input File Upload
        $('.brt-form-file-upload').hide();

        // Select file button click event
        $('.brt-file-wrapper').delegate('.brt-select-file-button', 'click', function() {
            var self = $(this),
                parent = $(this).parents(".brt-file-wrapper"),
                inputfile = parent.find('input[type="file"]');
            inputfile.trigger('click');
            return false;
        });

        $(".brt-file-wrapper").each(function(){
            checkFile($(this));
        });
        // Input file change event
        $('.brt-file-wrapper').delegate('input[type="file"]', 'change', function() {
            var nameFile = $(this).val().replace(/\\/g, '/').replace(/.*\//, ''),
                parent = $(this).parents(".brt-file-wrapper");
            parent.find('.file-hidden-value').val(nameFile);
            parent.find('.img-name').html(nameFile);
            readURL(this,parent);
            parent.find(".brt-remove-file-button").show();
        });
        /* Remove media selected */
        $(document).delegate(".brt-remove-file-button",'click',function(event){
            event.preventDefault();
            var mediaWrapper = $(this).parents(".brt-file-wrapper");
            mediaWrapper.find(".img-preview").attr("src", Drupal.settings.themeDir + '/theme-settings/img/no_image.png');
            mediaWrapper.find(".brt-remove-file-button").hide();
            mediaWrapper.find(".img-name").empty();
            mediaWrapper.find("input.file-hidden-value").val('');

        });

        $(".brt-media-wrapper").each(function(){
            checkMedia($(this));
        });
        /* Media popup click event */
        $(document).delegate(".media-select-button",'click',function(event){
            event.preventDefault();
            var mediaWrapper = $(this).parents(".brt-media-wrapper");
            Drupal.media.popups.mediaBrowser(function(files) {
                var file = files[0],
                    inputVal = {"fid":file.fid,"url":file.url,"name":file.filename};
                $("div.preview", mediaWrapper).html('<img alt=" ' + file.filename + ' " class="img-preview" src="' + file.url + '" /><p class="img-name"> ' +file.filename+ '</p>');
                $("input.media-hidden-value", mediaWrapper).val(JSON.stringify(inputVal));
                if(file.filename != null) {
                    $(".media-remove-button", mediaWrapper).show();
                }
            });

        })
        /* Remove media selected */
        $(document).delegate(".media-remove-button",'click',function(event){
            event.preventDefault();
            var mediaWrapper = $(this).parents(".brt-media-wrapper");
            mediaWrapper.find(".img-preview").attr("src", Drupal.settings.themePath + '/theme-settings/img/no_image.png');
            mediaWrapper.find(".media-remove-button").hide();
            mediaWrapper.find(".img-name").empty();
            mediaWrapper.find("input.media-hidden-value").val('');

        });


    });
// We need to check media image exist to display remove button
    function checkMedia(instance) {
        var existImg = false,
            hiddenVal = instance.find("input.media-hidden-value");
        if(hiddenVal.val() != 0) { instance.find(".media-remove-button").show() }
    }
// We need to check media image exist to display remove button
    function checkFile(instance) {
        var hiddenVal = instance.find("input.file-hidden-value");
        if($(hiddenVal).val() != 0 && $(hiddenVal).val() != "" && $(hiddenVal).val() != null) { instance.find(".brt-remove-file-button").show() }
    }

})(jQuery);
////////////////////////////////////////////////////// Add more content ////////////////////////////////////////////////
(function($){

    jQuery(document).ready(function(){

/////////////////////////////////////////////////// Icon Picker ////////////////////////////////////////////////////////

        function loadIcon(Obj) {
            if(Obj == null) {
                $(".icon-picker").each(function(){
                    var $self = $(this),
                        realWrap = $self.find("fieldset:first-child"),
                        title = $self.find(".fieldset-title").text().replace("Hide",""),
                        id = realWrap.find("select").attr("id");
                    var optSelect = $("#"+id).find("option:selected");
                    var arrIconValue = optSelect.val().split("|");
                    /* Wrap some html and prepare fake icon select */
                    $self.append('<div class="icon-wrapper">' +
                        '<div class="formRow"><label>'+title+'</label><div class="formRight">' +
                        '<a class="icon-dialog-open" data-id="'+id+'-fake" href="#"><div class="icon-preview"><i class="'+arrIconValue[0]+'  '+arrIconValue[1]+'"></i></div></a>' +
                        '</div><div id="'+id+'-fake" class="icon-markup">'+icFake+'</div></div></div>');
                    /* Hide real select */
                    realWrap.hide();
                    /* Create dialog */
                    $("#"+id+"-fake").dialog({
                        draggable: false,
                        autoOpen: false,
                        modal: true,
                        width: "88%",
                        minHeight: 400,
                        resizable: false,
                        dialogClass: "icon-dialog",
                        closeText: "Close",
                        title: "Icon Picker Dialog",
                        open: function(event,ui) {
                            $("body").addClass("modal-background");

                        },
                        close: function(event,ui) {
                            $("body").removeClass("modal-background");
                        }
                    })
                });
            } else {
                var realWrap = Obj.find(".icon-picker fieldset:first-child"),
                    id = realWrap.find("select").attr("id");
                Obj.find(".icon-dialog-open").attr("data-id",""+id+"-fake");
                Obj.find(".icon-wrapper").append('<div id="'+id+'-fake" class="icon-markup">'+icFake+'</div>');
                console.log(id);
                /* Create dialog */
                $("#"+id+"-fake").dialog({
                    draggable: false,
                    autoOpen: false,
                    modal: true,
                    width: "88%",
                    minHeight: 400,
                    resizable: false,
                    closeText: "Close",
                    dialogClass: "icon-dialog",
                    title: "Icon Picker Dialog",
                   open: function(event,ui) {
                        $("body").addClass("modal-background");
                    },
                    close: function(event,ui) {
                        $("body").removeClass("modal-background");
                    }
                })
            }
            iconDialog();
            clickIcon();

        }


        /* Open dialog */
        function iconDialog () {
            $(".icon-dialog-open").unbind('click').click(function(){
                /* Get id to open dialog */
                var id = $(this).attr("data-id");
                console.log(id);
                $("#"+id).dialog("open");
                return false;
            });
        }

        /* Fake Icon click event */
        function clickIcon() {
            $(".fake-icon").unbind('click').click(function(){
                /* Get select id */
                var id = $(this).parent().parent().parent().attr("id").replace("-fake",""),
                    $select = $("#"+id),
                    iconValue = $(this).attr("data-icon"),
                    iconName = $(this).attr("icon-name"),
                    iconBundle = $(this).attr("data-bundle"),
                    newIcon = '<i class="'+iconBundle+' '+iconName+'"></i>';
                /* Replace icon preview*/
                $select.parent().parent().parent().parent().parent().find('.icon-preview').html(newIcon);
                /* Replace icon value in select */
                $select.find('option[value="'+iconValue+'"]').attr('selected',true);
                $("#"+id+"-fake").dialog("close");
                return false;
            })
        }


    })

})(jQuery);

