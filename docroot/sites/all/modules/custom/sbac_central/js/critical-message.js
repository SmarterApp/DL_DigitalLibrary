(function($) {
    Drupal.behaviors.criticalMessageBehaviour = {};
    Drupal.behaviors.criticalMessageBehaviour.attach = function() {
        var showMessage = Drupal.settings.sbac_central.showCriticalMessage;
        var message = Drupal.settings.sbac_central.message;
        if (true === showMessage) {
            Drupal.CTools.Modal.show();
            $('#modal-title').html(Drupal.t('Important Notice', {}, ''));
            $('#modal-content').html(message);
            $(".cr-msg").click(function() {
                $.get('/sbac-central-shown-message', function() {
                    Drupal.CTools.Modal.dismiss();
                });
                return false;
            });
        }
    };
}) (jQuery);