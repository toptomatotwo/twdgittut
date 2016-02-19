(function($) {
  var iconPreview = {
    init: function(){
      _this = this;
      _this.fakeIcon();
      _this.iconDialog();
      _this.iconSelect();
    },
    fakeIcon: function(){
      $('.field-type-icon-field:not(.icon-process)').each(function(index,value){
        var $self = $(this),
        parentID = $self.attr('id');
        id = $self.find('select').attr('id');
        $self.append('<div class="icon-wrapper">' +
                      '<a class="icon-dialog-open" data-id="'+id+'-fake" href="#"><div class="icon-preview">Select Icon:'+_this.currentIcon(id)+'</div></a>' +
                      '</div><div id="'+id+'-fake" data-parentid="'+parentID+'" data-id="'+id+'" class="icon-markup">'+_this.iconContent(id)+'</div>');
        $self.addClass('icon-process');
        $self.find('.form-wrapper').hide();              
        $("#"+id+"-fake").dialog({
        draggable: false,
        autoOpen: false,
        modal: true,
        width: "80%",
        minHeight: 400,
        resizable: false,
        dialogClass: "icon-dialog",
        title: "Icon Picker Dialog"
      });
      });
    },
    iconSelect: function(){
      $(".fake-icon").unbind('click').click(function(){
        /* Get select id */
        $('.fake-con').removeClass('selected');
        $(this).addClass('selected');
        parentID = $(this).parent('.icon-markup').data('parentid');
        id = $(this).parent('.icon-markup').data('id');
        currentClass = $(this).attr('class');
        iconValue = $(this).data('value');
        /* Replace icon value in select */
        $('#'+id).find('option[value="'+iconValue+'"]').attr('selected',true);
        $('#'+parentID).find('.current-icon').removeClass().addClass(currentClass).addClass('current-icon')
        $("#"+id+"-fake").dialog("close");
        return false;
      })
    },
    iconDialog: function(){
      $(".icon-dialog-open").unbind('click').click(function(){
        /* Get id to open dialog */
        var id = $(this).data("id");
        $("#"+id).dialog("open");
        return false;
      });
    },
    currentIcon: function(id){
        var optSelect = $('#'+id).find('optgroup option:selected');
        if(optSelect[0]){
          var arrIconValue = optSelect[0].value.split("|");
          arrIconValue[2] = (arrIconValue[0] == 'font_awesome') ? 'fa' : 'simpleline';
          icon =  '<i class="fake-icon current-icon '+arrIconValue[2]+'  '+arrIconValue[1]+'"></i>'; 
        }
        else{
          icon = '<i class="current-icon"></i>';
        }
        return icon;
    },
    iconContent: function(id){
      var option = $('#'+id).find('option');
      var content_icon_preview = '';
      $.each(option,function(index,values){
        if(index != 1){
          optionClass = values.value.split("|");
          optionClass[2] = (optionClass[0] == 'font_awesome') ? 'fake-icon fa' : 'fake-icon simpleline';
          selected = (values.selected) ? 'selected' : '';
        }
       content_icon_preview += '<i class="'+selected+''+optionClass[2]+' '+optionClass[1]+'" data-value="'+values.value+'"></i>';
      });
      return content_icon_preview;
      
    }
  }
  Drupal.behaviors.preview_icon = {  
    attach: function(context, settings) {
      iconPreview.init();
    }
  };
}(jQuery));
