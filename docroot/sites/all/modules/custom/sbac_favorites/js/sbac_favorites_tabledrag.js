(function ($, Drupal) {
    /**
     * Invalidate swap check if the row target is not of the same parent
     * So we can only sort elements under the same parent and not move them to another parent
     *
     * @override Drupal.tableDrag.row.isValidSwap
     */
    // Keep the original implementation - we still need it.
    Drupal.tableDrag.prototype.row.prototype._isValidSwap = Drupal.tableDrag.prototype.row.prototype.isValidSwap;
    Drupal.tableDrag.prototype.row.prototype.isValidSwap = function(row) {
      if (this.indentEnabled) {
        if (row && $('.favorite-item-pid', this.element).val() !== $('.favorite-item-pid', row).val()) {
          return false;
        }

        if ($('.favorite-item-id', this.element).val() == 0 || (row && $('.favorite-item-id', row).val() == 0)) {
          return false;
        }
      }

      // Return the original result.
      return this._isValidSwap(row);
    };

    /**
     * Only allow two indent levels, 0 for root and 1 for leafs
     *
     * @override Drupal.tableDrag.row.validIndentInterval
     */
    Drupal.tableDrag.prototype.row.prototype.validIndentInterval = function (prevRow, nextRow) {
      if ($(this.element).is('.tabledrag-root')) {
          return { 'min': 0, 'max': 0 };
      } else {
          return { 'min': 1, 'max': 1 };
      }
    };

    /**
     * Add collapsible sections
     *
     * @override Drupal.tableDrag.prototype.initColums
     */
    Drupal.tableDrag.prototype._initColumns = Drupal.tableDrag.prototype.initColumns;
    Drupal.tableDrag.prototype.initColumns = function () {
        this._initColumns();

        $('tr.tabledrag-root .expander').toggle(
            function(){
                var target = $($(this).closest('tr.tabledrag-root'));
                target.nextUntil(':not(tr.tabledrag-leaf)').hide();
                target.removeClass('expanded').addClass('collapsed');
            },
            function(){
                var target = $($(this).closest('tr.tabledrag-root'));
                target.nextUntil(':not(tr.tabledrag-leaf)').show();
                target.removeClass('collapsed').addClass('expanded');
            }
        );
    };

    /**
     * Position the dragged element under the last children of the element target for swapping when moving down our dragged element.
     * Removed the indentation, since we can not change parent.
     * @override Drupal.tableDrag.row.dragRow
     */
    Drupal.tableDrag.prototype.dragRow = function (event, self) {
      if (self.dragObject) {
        self.currentMouseCoords = self.mouseCoords(event);

        var y = self.currentMouseCoords.y - self.dragObject.initMouseOffset.y;
        var x = self.currentMouseCoords.x - self.dragObject.initMouseOffset.x;

        // Check for row swapping and vertical scrolling.
        if (y != self.oldY) {
          self.rowObject.direction = y > self.oldY ? 'down' : 'up';
          self.oldY = y; // Update the old value.

          // Check if the window should be scrolled (and how fast).
          var scrollAmount = self.checkScroll(self.currentMouseCoords.y);
          // Stop any current scrolling.
          clearInterval(self.scrollInterval);
          // Continue scrolling if the mouse has moved in the scroll direction.
          if (scrollAmount > 0 && self.rowObject.direction == 'down' || scrollAmount < 0 && self.rowObject.direction == 'up') {
            self.setScroll(scrollAmount);
          }

          // If we have a valid target, perform the swap and restripe the table.
          var currentRow = self.findDropTargetRow(x, y);
          if (currentRow) {
            if (self.rowObject.direction == 'down') {

              /**
               * When going down we want to position the element after the last children and not right under the currentRow
               */
              // create a new row prototype with currentRow
              var rowObject = new self.row(currentRow, 'mouse', self.indentEnabled, self.maxDepth, false);
              // extract all children
              var childrenRows = rowObject.findChildren();
              // if we have children
              if (childrenRows.length > 0) {
                // we change the row to swap with the last children
                currentRow = childrenRows[childrenRows.length - 1];
              }

              self.rowObject.swap('after', currentRow, self);
            }
            else {
              self.rowObject.swap('before', currentRow, self);
            }
            self.restripeTable();
          }
        }
        /**
         * We have disabled the indentation changes since it is not possible to change parent.
         */

        return false;
      }
    };
})(jQuery, Drupal);