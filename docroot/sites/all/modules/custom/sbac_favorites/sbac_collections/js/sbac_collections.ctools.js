/**
 *
 */
Drupal.theme.prototype.CtoolsSbacCollectionsModal = function () {
var html = '';
  html += '  <div id="modalContent" class="modal-default node-collection-modal">';
  html += '    <div class="ctools-modal-content">';
  html += '      <div class="modal-header ui-dialog">';
  html += '        <button class="ui-button ui-widget ui-state-default ui-dialog-titlebar-close" title="'+Drupal.CTools.Modal.currentSettings.closeText+'" onclick="Drupal.CTools.Modal.dismiss();">';
  html += '          <span class="ui-button-icon-primary ui-icon ui-icon-closethick"></span>';
  html += '        </button>';
  html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
  html += '      </div>';
  html += '      <div id="modal-content" class="modal-content">';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';

  return html;
};