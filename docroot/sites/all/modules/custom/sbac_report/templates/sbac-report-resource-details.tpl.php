<div
  class="view view-contributed-resources view-id-contributed_resources view-display-id-resources_details" id="contriubted-resource-details">
  <div class="view-content">
    <table class="views-table cols-3">
      <thead>
      <tr>
        <th class="views-field views-field-title">
          Resource Title
        </th>
        <th class="views-field views-field-created active">
          <a href="<?php echo $data['table_created_query']; ?>" title="sort by Contribution Date"class="active">Contribution Date
          <?php
            if (isset($data['created_image'])) {
              echo $data['created_image'];
            }
          ?>
          </a>
        </th>
        <th class="views-field views-field-state">
          <a href="<?php echo $data['table_state_query']; ?>" title="sort by Post Status" class="active">Post Status
            <?php
            if (isset($data['state_image'])) {
              echo $data['state_image'];
            }
            ?>
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