(function ($) {
    $(document).ready(function () {
        //Define spectrum
        $(".form-colorpicker").spectrum({
            showAlpha: true,
            showInput: true,
            allowEmpty: true,
            showInitial: true,
            preferredFormat: "hex3"
        });


        // Slider range using for opacity
        $(".slider-range").each(function () {
            var $self = $(this),
                id = $(this).attr('id'),
                max = $(this).attr('data-max'),
                min = $(this).attr('data-min'),
                value = $(this).attr('data-value'),
                divine = $(this).attr("data-divine");

            // Append an element to make it slider range
            $(this).parent().append("<div id='" + id + "-slider'></div>");
            // Call jquery slider ui
            $("#" + id + "-slider").slider({
                range: "min",
                value: value * divine,
                min: min,
                max: max,
                slide: function (event, ui) {
                    $self.val((ui.value) / divine);
                }
            });
            // Put value of slider range into input
            $self.val(($("#" + id + "-slider").slider("value")) / divine);
        });

        var moduleDir = Drupal.settings.moduleDir;
        uploadForm.init();
        
        $(".unlimited-settings").UnlimitedSettings();
    });

    // =========== OBJECT, FUNCTION DEFINE ============== //

        var moduleDir = Drupal.settings.moduleDir;
    var uploadForm = {
        init: function() {
            console.log('init');
            var mediaInstance = $('.md-media-wrapper');
            var fileInstance = $('.md-file-wrapper');
            
            this.add();
            this.remove();
            this.inputChange();
            this.checkMedia(mediaInstance);
            this.checkFile(fileInstance);
        },
        add: function () {
            /* Media popup click event */
            $(".md-media-wrapper").delegate(".media-select-button",'click',function(event){
                event.preventDefault();
                var mediaWrapper = $(this).parents(".md-media-wrapper");
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
            $('.md-file-wrapper').delegate('.md-select-file-button', 'click', function() {
                var self = $(this),
                    parent = $(this).parents(".md-file-wrapper"),
                    inputfile = parent.find('input[type="file"]');
                inputfile.trigger('click');
                return false;
            });

        },
        remove: function () {
            /* Remove media selected */
            $(".md-media-wrapper").delegate(".media-remove-button",'click',function(event){
                var moduleDir = Drupal.settings.moduleDir;
                event.preventDefault();
                var mediaWrapper = $(this).parents(".md-media-wrapper");
                mediaWrapper.find(".img-preview").attr("src", moduleDir + '/imgs/no_image.png');
                mediaWrapper.find(".media-remove-button").hide();
                mediaWrapper.find(".img-name").empty();
                mediaWrapper.find("input.media-hidden-value").val('').trigger('change');
                return false;
            });
            /* Remove media selected */
            $('.md-file-wrapper').delegate(".md-remove-file-button",'click',function(event){
                var moduleDir = Drupal.settings.moduleDir;
                event.preventDefault();
                var mediaWrapper = $(this).parents(".md-file-wrapper");
                mediaWrapper.find(".img-preview").attr("src", moduleDir + '/imgs/no_image.png');
                mediaWrapper.find(".md-remove-file-button").hide();
                mediaWrapper.find(".img-name").empty();
                mediaWrapper.find("input.file-hidden-value").val('').trigger('change');
                return false;
            });
        },
        inputChange : function () {
            // Input file change event
            $('.md-file-wrapper').delegate('input[type="file"]', 'change', function() {
                var nameFile = $(this).val().replace(/\\/g, '/').replace(/.*\//, ''),
                    parent = $(this).parents(".md-file-wrapper");
                parent.find('.file-hidden-value').val(nameFile).trigger('change');
                parent.find('.img-name').html(nameFile);
                readURL(this,parent);
                parent.find(".md-remove-file-button").show();
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
            if($(hiddenVal).val() != 0 && $(hiddenVal).val() != "" && $(hiddenVal).val() != null) { instance.find(".md-remove-file-button").show() }
        }
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
                    container.find('.wrap-sortable').append(cloneItem);

                    that.updateObj(container);
                    that.formMedia();
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

                            $.each(formData,function(index,value) {
                                $(_item).find(':input[name="'+ formData[index].name +'"]').val(formData[index].value);

                                if(formData[index].name == 'form_media_hidden') {
                                    var mediaData = $.parseJSON(formData[index].value);
                                    if(mediaData != null) {
                                        $(_item).find(".img-preview").attr("src",mediaData.url);
                                        $(_item).find(".img-name").html(mediaData.name);
                                    }
                                }
                            })
                        });

                        that.updateValue(container);
                    }
                }


            },
            formMedia : function () {
                if(uploadForm != undefined)
                    uploadForm.init();
            },
            checkNumberItem: function (container) {
                var length = container.find('.wrap-sortable .sortable-item').length;
                if(length > 1 ) {
                    $(".us-remove-button").show();
                } else {
                    $(".us-remove-button").hide();
                }
            }
        };

        return this.each( function() {
            var self = $(this);
            UnlimitedObj.container = [];

            UnlimitedObj.container.push(self.attr('id'));

            UnlimitedObj.initObj();
        });
    };
})(jQuery);