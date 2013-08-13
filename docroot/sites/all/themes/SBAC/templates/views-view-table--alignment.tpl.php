<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
   <?php if (!empty($title) || !empty($caption)) : ?>
     <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <th><?php print t('Alignment'); ?></th>
        <th><?php print t('Alignment Type'); ?></th>
        <th><?php print t('Operations'); ?></th>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <tr>
        <td><?php print $row['field_education_alignment']; ?></td>
        <td><?php print $row['field_alignment_type']; ?></td>
        <td>
          <?php print $row['title']; ?>
          <?php print $row['edit_node']; ?>
          <?php print $row['delete_node']; ?>
        </td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>