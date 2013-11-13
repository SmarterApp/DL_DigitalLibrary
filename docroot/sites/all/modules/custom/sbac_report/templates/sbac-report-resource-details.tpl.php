<div
  class="view view-contributed-resources view-id-contributed_resources view-display-id-resources_details view-dom-id-d96c6ab07c06aa15ada0cc7b365049d5 jquery-once-1-processed">
  <div class="view-content">
    <table class="views-table cols-3">
      <thead>
      <tr>
        <th class="views-field views-field-title">
          Resource Title
        </th>
        <th class="views-field views-field-created active">
          <a href="/reports?items_per_page=5&amp;order=created&amp;sort=asc" title="sort by Contribution Date"class="active">Contribution Date
            <img typeof="foaf:Image" src="http://stage.smarterbalancedlibrary.org/misc/arrow-asc.png" width="13" height="13" alt="sort ascending" title="sort ascending">
          </a>
        </th>
        <th class="views-field views-field-state">
          <a href="/reports?items_per_page=5&amp;order=state&amp;sort=asc" title="sort by Post Status" class="active">Post Status
          </a>
        </th>
      </tr>
      </thead>
      <tbody>
      <?php
        foreach ($rows as $row) {
          echo '<tr class="views-row-first views-row-last">';
          echo '<td class="views-field views-field-nid-active">' . $row[0] . '</td>';
          echo '<td class="views-field views-field-published">' . $row[1] . '</td>';
          echo '<td class="views-field views-field-sticky">' . $row[2] . '</td>';
          echo '</tr>';
        }
      ?>
      </tbody>
    </table>
  </div>
  <div class="view-filters large-3">
    <form class="ctools-auto-submit-full-form ctools-auto-submit-processed jquery-once-1-processed" action="/" method="get" id="views-exposed-form-contributed-resources-resources-details" accept-charset="UTF-8">
      <div>
        <div class="views-exposed-form">
          <div class="views-exposed-widgets clearfix">
            <div class="views-exposed-widget views-widget-per-page">
              <div class="form-item-error-holder"></div>
              <div class="form-item form-type-select form-item-items-per-page">
                <label for="edit-items-per-page">Display </label>
                <select id="edit-items-per-page" name="items_per_page" class="form-select">
                  <option value="5" selected="selected">Up to 5</option>
                  <option value="10">Up to 10</option>
                  <option value="15">Up to 15</option>
                  <option value="All">All</option>
                </select>
              </div>
            </div>
            <div class="views-exposed-widget views-submit-button">
              <button class="ctools-use-ajax ctools-auto-submit-click js-hide form-submit" id="edit-submit-contributed-resources" name="" value="Apply" type="submit">Apply</button>
            </div>
          </div>
        </div>
      </div>
    </form>
  </div>


</div>