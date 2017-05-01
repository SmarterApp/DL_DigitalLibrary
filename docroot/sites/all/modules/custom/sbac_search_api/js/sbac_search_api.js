/**
 * Created by jbaker on 4/21/17.
 */
(function ($) {
  function plusMinusToggler(selector) {
    $(selector).each(function () {
      var $clickedlist = $(this).parent().parent().siblings('.item-list').children('ul');
      if ($clickedlist.hasClass('expanded')) {
        if (!$(this).hasClass('minus-sign')) {
          $(this).addClass('minus-sign');
        }
        if ($(this).hasClass('plus-sign')) {
          $(this).removeClass('plus-sign');
        }
      } else {
        if ($(this).hasClass('minus-sign')) {
          $(this).removeClass('minus-sign');
        }
        if (!$(this).hasClass('plus-sign')) {
          $(this).addClass('plus-sign');
        }
      }
    });
  }

  $(document).ready(function () {
    plusMinusToggler('a .facetapi-collapsible-handle');

    $('a .facetapi-collapsible-handle').click(function (event) {
      plusMinusToggler(this);
    });

    $('.facetapi-facet').each(function() {
      var href = $(this).children('a.facetapi-active, a.facetapi-inactive').attr('href');
      $(this).prepend('<a class="checkbox-spacer" href="' + href + '">&nbsp;</a>');
    });

    $('.default-sort').click(function (e) {
      $(this).toggleClass('active');
      $('.search-api-sorts').toggle();
    })
  });
})(jQuery);