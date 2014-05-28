/**
 * This is the HTML output for the modal.
 *
 * sbac_flag.module, function hook_form_alter, line 255
 * this is where I add the modalTheme which declares this
 * theme output for that modal.
 *
 * @returns {string}
 * @constructor
 */

Drupal.theme.prototype.CtoolSbacForumModal = function () {
  var html = ''
  html += '  <div id="ctools-modal" class="small">'
  html += '    <div class="ctools-modal-content small">' // panels-modal-content
  html += '      <div class="modal-header">';
  html += '        <a class="close" href="#">';
  html +=            Drupal.CTools.Modal.currentSettings.closeText + Drupal.CTools.Modal.currentSettings.closeImage;
  html += '        </a>';
  html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
  html += '      </div>';
  html += '      <div id="modal-content" class="modal-content">';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';

  return html;
}

