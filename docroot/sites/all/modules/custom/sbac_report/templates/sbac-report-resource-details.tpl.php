<div
  class="view view-contributed-resources view-id-contributed_resources view-display-id-resources_details">
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
        $class = 'even';
        foreach ($rows as $row) {
          echo '<tr class="' . $class . '">';
          echo '<td class="views-field views-field-nid-active">' . $row->title . '</td>';
          echo '<td class="views-field views-field-published">' . $row->contribution_date . '</td>';
          echo '<td class="views-field views-field-sticky">' . $row->state . '</td>';
          echo '</tr>';
          ($class == 'even' ? $class = 'odd' : $class = 'even');
        }
      ?>
      </tbody>
    </table>
  </div>
  <div class="view-filters large-3">
    <?php print $form; ?>
  </div>


</div>