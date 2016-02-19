;(function($){
    var optionsConfig = {
        currentOps : [],
        init: function(){
            var that = this,
                currentOps = that.currentOps;
            // Get all selected options
            $("input.hd-options:checked").each(function(){
                var self = $(this),
                selectedOps = self.val();
                if(selectedOps != undefined) {
                    currentOps.push(selectedOps);
                }
            });
            console.log(currentOps);
            $('input.hd-options').click(function(){
                var status = 'checked';
                    id = $(this).parents(".form-checkboxes").attr('id'),
                    value = $(this).val();
                if($(this).attr('checked') == 'checked') {

                } else {
                    status = 'uncheck';
                }
                that.checkOps(value,status);
                that.update();
            });
            that.update();
        },
        update: function(){
            var currentOps = this.currentOps;
            console.log(currentOps);
            $("input.hd-options").each(function(){
                var self = $(this),
                    val = self.val();
                var index = currentOps.indexOf(val);
                var checkAttr = self.attr('checked');
                var disabledAttr = self.attr('disabled');
                if(typeof checkAttr !== typeof undefined && checkAttr !== false) {

                } else {
                    if(val != undefined && (typeof currentOps[index] !== "undefined")) {
                        self.attr('disabled','disabled');
                    } else {
                        if(typeof disabledAttr !== typeof undefined && disabledAttr !== false) {
                            self.removeAttr("disabled");
                        }
                    }
                }
            });

        },
        checkOps: function(opCheck,status) {
            console.log(status);
            var currentOps = this.currentOps;
            if(status == 'checked') {
                if(!currentOps[opCheck]) {
                    currentOps.push(opCheck);
                }
            }
            if(status == 'uncheck') {
                var i = currentOps.indexOf(opCheck);
                if(i != -1) {
                    currentOps.splice(i, 1);
                }
            }
            console.log(currentOps);
        }
    };
    $(document).ready(function(){
        optionsConfig.init();
    });
})(jQuery);