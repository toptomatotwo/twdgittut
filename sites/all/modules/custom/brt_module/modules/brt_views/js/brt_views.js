(function($) {
  var SortAnimate = {
    init: function(){
      _this = this;
      _this.addClick();
      _this.deleteAnimate();
    },
    addClick: function(){
      $('.add-click').click(function(){
        var array_option = $('.animate-select').find('option:selected');
        _this.addTable(array_option);
      });
    },
    addTable: function(array_option){
        var content = '';
        $.each(array_option,function(index,value){
          var animate = $(this).attr('value');
          content += '<li><span class="animate-value">'+animate+'<i>|</i></span> <span class="delete-animate"></span></li>';
        });
        $('#sortable').append(content);
        _this.addInput('#sortable');
        _this.updateSort();

    },
    deleteAnimate: function(){
      $('#sortable').on('click','.delete-animate',function(){
        $(this).parents('li').remove();
        _this.addInput('#sortable');
      });
    },
    addInput: function(select){
      text = $(select).find('.animate-value').text();
      $('.animate-value-hidden').attr('value',text);
    },
    updateSort: function(){
      $("#sortable" ).sortable({
        update: function( event, ui ) {
            _this.addInput('#sortable');
        }
      });
    }
  }
  Drupal.behaviors.SortAnimate = {
    attach: function(context, settings) {
      $('#sortable').sortable();
      SortAnimate.init();
    }
  };
}(jQuery));
