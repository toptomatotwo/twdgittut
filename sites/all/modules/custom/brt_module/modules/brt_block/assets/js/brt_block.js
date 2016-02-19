;(function($, window, undefined){
    var moduleDir = Drupal.settings.moduleDir;

    $(window).load(function(){
        fakeSelectIcon.init();
        uploadForm.init();
    });

    $(document).ready(function(){

        $(".unlimited-settings").UnlimitedSettings();

        ///////////////////// JQUERY UI SlIDER RANGE //////////////////////////////////////
        $(".slider-range").each(function(){
            var $self = $(this),
                id = $(this).attr('id'),
                max = $(this).data('max'),
                min = $(this).data('min'),
                defaultValue = $(this).data('value');
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

        ////////////////////// Color Picker ////////////////////////////////////////////
        $(".form-colorpicker").spectrum({
            showAlpha: true,
            showInput: true,
            allowEmpty:true,
            showInitial: true,
            preferredFormat: "hex3"
        })

        ///////////////////// Fake Select ////////////////////////////////
        $('.fake-select').fakeSelect();


        /* Load Icon Dialog Fake Markup */
        var icFake = Drupal.settings.icFake;
        loadIcon(null);
        iconDialog();
        clickIcon();


    });

    // =========== OBJECT, FUNCTION DEFINE ============== //

    var uploadForm = {
        init: function() {
            var mediaInstance = $('.brt-media-wrapper');
            var fileInstance = $('.brt-file-wrapper');
            this.add();
            this.remove();
            this.inputChange();
            this.checkMedia(mediaInstance);
            this.checkFile(fileInstance);
        },
        add: function () {
            /* Media popup click event */
            $(".brt-media-wrapper").delegate(".media-select-button",'click',function(event){
                event.preventDefault();
                var mediaWrapper = $(this).parents(".brt-media-wrapper");
                Drupal.media.popups.mediaBrowser(function(files) {
                    var file = files[0],
                        inputVal = {"fid":file.fid,"url":file.url,"name":file.filename};
                    $("div.preview", mediaWrapper).html('<img alt=" ' + file.filename + ' " class="img-preview" src="' + file.url + '" /><p class="img-name"> ' +file.filename+ '</p>');
                    $("input.media-hidden-value", mediaWrapper).val(JSON.stringify(inputVal)).trigger('change');
                    if(file.filename != null) {
                        $(".media-remove-button", mediaWrapper).show();
                    }
                });
                return false;
            });
            // Select file button click event
            $('.brt-file-wrapper').delegate('.brt-select-file-button', 'click', function() {
                var self = $(this),
                    parent = $(this).parents(".brt-file-wrapper"),
                    inputfile = parent.find('input[type="file"]');
                inputfile.trigger('click');
                return false;
            });

        },
        remove: function () {
            /* Remove media selected */
            $(".brt-media-wrapper").delegate(".media-remove-button",'click',function(event){
                event.preventDefault();
                var mediaWrapper = $(this).parents(".brt-media-wrapper");
                mediaWrapper.find(".img-preview").attr("src", moduleDir + '/assets/images/no_image.png');
                mediaWrapper.find(".media-remove-button").hide();
                mediaWrapper.find(".img-name").empty();
                mediaWrapper.find("input.media-hidden-value").val('').trigger('change');
                return false;
            });
            /* Remove media selected */
            $('.brt-file-wrapper').delegate(".brt-remove-file-button",'click',function(event){
                event.preventDefault();
                var mediaWrapper = $(this).parents(".brt-file-wrapper");
                mediaWrapper.find(".img-preview").attr("src", moduleDir + '/assets/images/no_image.png');
                mediaWrapper.find(".brt-remove-file-button").hide();
                mediaWrapper.find(".img-name").empty();
                mediaWrapper.find("input.file-hidden-value").val('').trigger('change');
                return false;
            });
        },
        inputChange : function () {
            // Input file change event
            $('.brt-file-wrapper').delegate('input[type="file"]', 'change', function() {
                var nameFile = $(this).val().replace(/\\/g, '/').replace(/.*\//, ''),
                    parent = $(this).parents(".brt-file-wrapper");
                parent.find('.file-hidden-value').val(nameFile).trigger('change');
                parent.find('.img-name').html(nameFile);
                readURL(this,parent);
                parent.find(".brt-remove-file-button").show();
                return false;
            });
        },
        checkMedia: function (instance) {
            var existImg = false,
                hiddenVal = instance.find("input.media-hidden-value");
            if(hiddenVal.val() != 0) { instance.find(".media-remove-button").show() }
        },
        checkFile: function (instance) {
            var hiddenVal = instance.find("input.file-hidden-value");
            if($(hiddenVal).val() != 0 && $(hiddenVal).val() != "" && $(hiddenVal).val() != null) { instance.find(".brt-remove-file-button").show() }
        }
    }

/////////////////////////////////////////////////// Icon Picker ////////////////////////////////////////////////////////
    function loadIcon(Obj) {
        var icFake = Drupal.settings.icFake;
        if(Obj == null) {
            $(".icon-picker").each(function(){
                var $self = $(this),
                    realWrap = $self.find("fieldset:first-child"),
                    title = $self.find(".fieldset-title").text().replace("Hide",""),
                    id = realWrap.find("select").attr("id");
                var optSelect = $self.find("option:selected");
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
                width: "80%",
                minHeight: 400,
                resizable: false,
                dialogClass: "icon-dialog",
                closeText: "X",
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
        $(".icon-dialog-open").unbind('click').click(function(e){
            e.preventDefault();
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
            //$select.find('option[value="'+iconValue+'"]').attr('selected',true);
            $select.val(''+iconValue+'').trigger('change');
            $("#"+id+"-fake").dialog("close");
            return false;
        })
    }
    ////////////////// Fake select Pattern BG////////////////////////

    $.fn.fakeSelect = function() {
        return this.each(function() {
            var $self = $(this),
                id = $self.attr("id"),
                numberItems = $("#"+ id + ' option').length,
                $previewWrap = $self.parents(".fake-select-wrapper").find(".fake-select-preview"),
                selected = $("#"+ id).val();


            //Prepare preview html
            $htmlPreview = '';
            for ($i = 0; $i <= numberItems; $i++) {
                $tmpval = $("#"+ id + " option:eq("+$i+")").val();
                if ($tmpval) {
                    $htmlPreview += '<div id="fsItem-'+$tmpval+'" class="fsItem"></div>';
                }
            }
            // Append to fake div
            $previewWrap.html($htmlPreview);

            // Check current selected option and set fake selected
            $("#fsItem-"+ selected).addClass("selected");

            // Event clicking fake select item
            $previewWrap.find(".fsItem").each(function() {
                $(this).click(function(){
                    $previewWrap.find(".selected").removeClass('selected');

                    $(this).addClass('selected');

                    $("#"+ id + " option[selected]").removeAttr("selected");

                    tmpindex = $(this).attr('id').replace("fsItem-", "")
                    $("#"+ id + " option[value="+tmpindex+"]").attr("selected", "selected");

                });
            });
            // Hide the real select
            $self.hide();
        });
    }




    $.fn.UnlimitedSettings = function (options){

        // Establish our default settings
        var settings = $.extend({

        }, options);

        var UnlimitedObj = {
            container : [],
            initObj : function () {
                var _this = this,
                    container = $("#" + _this.container[0]);

                _this.initSortable(container);

                _this.cloneObj(container);
                _this.removeObj(container);
                _this.parseData(container);
                _this.checkNumberItem(container);
                _this.changeInput(container);

                _this.updateIndexes(container);


            },
            cloneObj : function (container) {
                var that = this;
                $(container).delegate('.us-add-button','click',function(event){
                    event.preventDefault();

                    var cloneItem = container.find('.sortable-item:last-child').clone();
                    cloneItem.data('index',(cloneItem.data('index') + 1));
                    var iconForm = cloneItem.find('.icon-picker select'),
                        iconFormId = iconForm.attr('id'),
                        newId = iconFormId+'-'+(cloneItem.data('index') + 1);
                    console.log(newId);
                    cloneItem.find('.icon-picker select').attr('id',newId);
                    container.find('.wrap-sortable').append(cloneItem);

                    that.updateObj(container);
                    that.formMedia();
                    loadIcon(cloneItem);
                })
            },
            removeObj : function (container) {
                var that = this;
                $(container).delegate('.us-remove-button','click',function(event){
                    event.preventDefault();

                    $(this).parents('.sortable-item').remove();

                    that.updateObj(container);
                })
            },
            updateObj : function (container) {
                this.checkNumberItem(container);
                this.changeInput(container);
                this.updateIndexes(container);
                this.updateValue(container);
            },
            initSortable : function (container) {
                var that = this;

                container.find('.wrap-sortable').sortable({
                    update: function( event, ui ) {
                        that.updateValue(container);
                    }
                });

            },
            updateSortable : function (container) {
                container.find('.wrap-sortable').refresh();
            },
            updateIndexes : function (container) {
                container.find(".sortable-item").each(function(index,element){
                    $(this).attr('data-index',index);
                });
            },
            changeInput :  function (container) {
                var that = this;
                container.find(':input').not('.us-hidden-value').each(function(){

                    $(this).on('change',function(){
                        that.updateValue(container);
                    }).change();

                })
            },
            updateValue : function (container) {
                var that = this,
                    jsData = [];

                container.find(".sortable-item").each(function(index, element) {
                    var itemData = $(this).find(':input').not('.us-hidden-value').serializeArray({ checkboxesAsBools: true });
                    jsData[index] = itemData;
                });

                var jsJson = JSON.stringify(jsData);
                console.log(jsJson);
                container.find('.us-hidden-value').val(jsJson);

            },
            parseData : function (container) {
                var that = this,
                    data = $.parseJSON(container.find(".us-hidden-value").val()),
                    wrap = container.find(".wrap-sortable"),
                    itemHtml = wrap.find(".sortable-item:first-child").clone().wrap('<div></div>').parent().html();
                if(data != undefined) {

                    if(data.length > 0) {
                        wrap.empty();

                        $.each(data, function(index, value) {
                            wrap.append(itemHtml);

                            var _item = wrap.find('.sortable-item').eq(index);

                            $(_item).data('index',index);

                            var formData = value;
                            console.log(formData);
                            $.each(formData,function(index,value) {
                                $(_item).find(':input[name="'+ formData[index].name +'"]').val(formData[index].value).trigger('change');
                                if(formData[index].name == 'hd_social_icon[icon]') {
                                    $(_item).find(':input[name="'+ formData[index].name +'"] option[value="'+formData[index].value+'"]').attr('selected','selected');
                                }
                                if(formData[index].name == 'form_media_hidden') {
                                    var mediaData = $.parseJSON(formData[index].value);
                                    if(mediaData != null) {
                                        $(_item).find(".img-preview").attr("src",mediaData.url);
                                        $(_item).find(".img-name").html(mediaData.name);
                                    }
                                }
                            });
                        });

                        that.updateValue(container);
                    }
                }


            },
            formMedia : function () {     
                if(uploadForm != undefined)
                    uploadForm.init();
            },
            formIcon : function () {

            },
            checkNumberItem: function (container) {
                var length = container.find('.wrap-sortable .sortable-item').length;
                if(length > 1 ) {
                    $(".us-remove-button").show();
                } else {
                    $(".us-remove-button").hide();
                }
            }
        }

        return this.each( function() {
            var self = $(this);
            UnlimitedObj.container = [];

            UnlimitedObj.container.push(self.attr('id'));

            UnlimitedObj.initObj();
        });

    }
    // Fake Select icon
    var fakeSelectIcon = {
        init: function(){
            _that = this;
            _that.fakeList();
            _that.dialogFakelist();
            _that.iconSelect();
        },
        fakeList: function(){
            $('.form-select-icon').each(function(){
                var self = $(this),
                    list = '',
                    option_select,
                    font_select,
                    class_select,
                    id   = self.data('selectdiv'),
                    options = self.find('option');
                self.hide();
                $.each(options,function(index,value){
                    select = value.selected;
                    value  = value.value;
                    value_array = value.split("|");
                    font = (value_array[0] == 'fa') ? 'fa' : '';
                    if(select == true){
                        font_select   = font;
                        class_select  = value_array[1];
                    }


                    list += '<li class="selected-'+select+' list-icon-fake" data-value="'+value+'"><i class="'+value_array[1]+' icon '+font+'"></i></li>';
                });
                self.before('<span data-dialog="'+id+'" class="pick-icon"><i class="'+font_select+' font '+class_select+'"></i></span>');
                //self.hide();
                self.after('<div id="'+id+'"  class="icon-dialog-parent">'+list+'</div>');
            });
        },
        dialogFakelist: function(){
            $('.icon-dialog-parent').dialog({
                draggable: false,
                autoOpen: false,
                modal: true,
                width: "80%",
                minHeight: 400,
                resizable: false,
                dialogClass: "icon-dialog",
                title: "Icon Picker Dialog",
                closeText: "X"
            });
            $(document).delegate('.pick-icon','click',function(e){
                $(this).parents('.wrap-sort').addClass('wrap-sort-pick');
                $(this).parents('.form-elements').find(".form-select-icon").addClass('select-selected');
                dialog = $(this).data('dialog');
                $('#'+dialog).dialog("open");
            });
            return false;
        },
        iconSelect: function(){
            $(document).delegate('.list-icon-fake','click',function(){
                var self   = $(this),
                    id     = self.parents('.icon-dialog-parent').attr('id'),
                    value  = self.data('value'),
                    text   = self.html(),
                    $select = $('.'+id).parents('.wrap-sort.wrap-sort-pick'),
                    $input  = $('.'+id).parents('.wrap-sort.wrap-sort-pick').next('.addmore-input-hidden');
                console.log(id);
                $('.list-icon-fake').removeClass('selected-true').addClass('selected-false');
                self.removeClass('selected-false').addClass('selected-true');
                $('.'+id+'.select-selected').find('option[value="'+value+'"]').attr('selected',true);
                $("#"+id).dialog("close");
                $("."+id+'.select-selected').parents(".input-select").find('.pick-icon').html('Choose icon: '+text);
                $("."+id+'.select-selected').removeClass('select-selected');
                _this.saveAddMore($select,$input);
                return false;
            });
        }
    }

})(jQuery,window,undefined);