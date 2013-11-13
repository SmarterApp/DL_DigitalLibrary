<div class="view view-contributed-resources view-id-contributed_resources view-display-id-resources_summary">
  <div class="view-content">
    <table class="views-table cols-3">
      <thead>
        <tr>
          <th class="views-field views-field-nid">Resources Contributed</th>
          <th class="views-field views-field-published">Contributed Resources Posted</th>
          <th class="views-field views-field-sticky">Contributed Resources Posted with Distinction</th>
        </tr>
      </thead>
      <tbody>
        <?php
          foreach ($rows as $row) {
            echo '<tr class="odd views-row-first views-row-last">';
            echo '<td class="views-field views-field-nid">' . $row[0] . '</td>';
            echo '<td class="views-field views-field-published">' . $row[1] . '</td>';
            echo '<td class="views-field views-field-sticky"> ' . $row[2] . '</td>';
            echo '</tr>';
          }
        ?>
      </tbody>
    </table>
  </div>
</div>