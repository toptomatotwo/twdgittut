(function($) {

    $.fn.UnlimitedSettings = function (options){

        // Establish our default settings
        var settings = $.extend({

        }, options);

        var UnlimitedObj = {
            container : [],
            initObj : function () {
                var _this = this,
                    container = $("#" + _this.container[0]);

                if($("#" + _this.container[0]).hasClass('enable-sortable')) {
                    _this.initSortable(container);
                }

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
// AddMore Fuction
    var Unlimited = {
        init: function(){

            _this = this;
            _this.activeAddMore(); // Function Active options select
            _this.clickAddMore();  // Event when click Addmore button
            _this.removeAddMore(); // Event when click Remove button
            _this.changeAddMore(); // Event when change value of form
            _this.sortAddMore();   // Save all value of form to hidden field
            _this.popupFrameMeida();
            _this.saveAddMore();

            var clickMedia;
        },
        activeAddMore: function(){
            $('.addmore-input-hidden').each(function(){
                var jsData = $(this).attr('value'),
                    jsData = JSON.parse(jsData);
            });
        },
        clickAddMore: function(){
            $(document).delegate('.addmore-button','click',function(e){
                e.preventDefault();
                var $self   = $(this),
                    $select = $self.next('.wrap-sort'),
                    $input  = $self.nextAll('.addmore-input-hidden');

                var clone = $(this).next('.wrap-sort').find('.draggable-item:first-child').clone();
                $self.next('.wrap-sort').append(clone);
                _that.dialogFakelist();
                _that.iconSelect();
                _this.changeAddMore();
                _this.saveAddMore($select,$input);
            });
        },
        removeAddMore: function(){
            $(document).delegate('.remove-addmore-button','click',function(e){
                e.preventDefault();
                var $self   = $(this),
                    $select = $self.parents('.wrap-sort'),
                    $input  = $self.parents('.wrap-sort').next('.addmore-input-hidden');
                $self.parent().remove();
                _this.saveAddMore($select,$input);
            });
        },
        changeAddMore: function(){
            $('.wrap-sort').find(':input').each(function(){
                if($(this).attr('type') == 'hidden'){

                }
                $(this).on('change',function(){
                    var $self   = $(this),
                        $select = $self.parents('.wrap-sort'),
                        $input  = $self.parents('.wrap-sort').next('.addmore-input-hidden');
                    _this.saveAddMore($select,$input);
                }).change();
                //media-wrapper

            })
        },
        popupFrameMeida: function(){
            $('.popup-media').on('click',function(e){
                var $self   = $(this),
                    $select = $self.parents('.wrap-sort'),
                    $input  = $self.parents('.wrap-sort').next('.addmore-input-hidden');
                clickMedia = $(this);
                Drupal.media.popups.mediaBrowser(_this.chooseMedia);
                e.preventDefault();
            });
        },
        chooseMedia: function(selected){
            clickMedia.prev().find("img").attr("src", selected[0].url).trigger("change");
            clickMedia.next().val(selected[0].fid);
            var $select = clickMedia.parents('.wrap-sort'),
                $input  = clickMedia.parents('.wrap-sort').next('.addmore-input-hidden');
            _this.saveAddMore($select,$input);
        },
        sortAddMore: function(){
            $('.wrap-sort').sortable({
                update: function( event, ui ) {
                    var $select = $(this),
                        $input  = $(this).next('.addmore-input-hidden');
                    _this.saveAddMore($select,$input);
                }
            });
        },
        saveAddMore: function(select,input){
            if(select){
                var jsObject = select.find(':input').serializeArray({ checkboxesAsBools: true });
                var jsData = JSON.stringify(jsObject);
                input.attr('value',jsData);
                select.removeClass('wrap-sort-pick');
            }
        }
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


    Drupal.behaviors.AddMore = {
        attach: function(context, settings) {
            Unlimited.init();
            fakeSelectIcon.init();
            $('.unlimited-settings').UnlimitedSettings();
        }
    };
}(jQuery));
