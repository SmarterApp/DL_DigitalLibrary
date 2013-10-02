<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
   <?php if (!empty($title) || !empty($caption)) : ?>
     <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <th><?php print t('Standard'); ?></th>
<!--        <th>--><?php //print t('Alignment Type'); ?><!--</th>-->
        <th><?php print t('Operations'); ?></th>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <?php
        $is_ela = $is_ma = FALSE;
        $alignment_node = node_load($row['nid']);
        $tid = $alignment_node->field_education_alignment['und'][0]['tid'];
        //dsm($tid);
        $tag_node = taxonomy_term_load($tid);
        //dsm($tag_node);
        $parents = taxonomy_get_parents_all($tid);
        //dsm($parents);

        $subject = array_pop($parents);

        if ($is_ela = ($subject->name == 'English / Language Arts')) {
           $grade = array_pop($parents);
           $claim = array_pop($parents);
        }
        elseif ($is_ma = ($subject->name == 'Math')) {
           $grade = array_pop($parents);
           $claim = array_pop($parents);
           $domain = array_pop($parents);
           $target = array_pop($parents);
           $emphasis = array_pop($parents);
        }
        else {
           //do nothing
        }
      ?>

      <tr id="term-<?php print $row['nid']; ?>">
        <td><?php print $tag_node->field_alignment_key['und'][0]['value']; ?></td>
        <!--<td><?php print $row['field_education_alignment']; ?></td>-->
<!--        <td>--><?php //print $row['field_alignment_type']; ?><!--</td>-->
        <td>
          <div class="read-more">
            <a href="" class=""><i class="accessibility foundicon-eyeball"></i></a>
            <div class="more description-hover">
              <div class="description-content">
              <h2><?php print $subject->name; ?></h2>
              <div class="ccss-standard">
                 <h2><?php print $tag_node->field_alignment_key['und'][0]['value']; ?></h2>
                 <?php print $tag_node->description; ?>
              </div>
              <div class="ccss-grade">
                <h3>Grade</h3>
                <?php
                  if (isset($grade)) {
                    print $grade->name;
                  }
                ?>
              </div>
              <div class="ccss-claim">
                <h3>Claim</h3>
                <?php if (isset($claim)): ?>
                  <h2>
                    <?php print $claim->field_alignment_shortname['und'][0]['value']; ?>
                  </h2>
                  <?php print $claim->description; ?>
                <?php endif; ?>
              </div>
              <?php if ($is_ma):?>
                  <div class="ccss-target">
                    <h3>Domain</h3>
                    <h2><?php print $domain->field_alignment_shortname['und'][0]['value']; ?></h2>
                    <?php print $domain->description; ?>
                  </div>
                  <div class="ccss-target">
                    <h3>Target</h3>
                    <h2><?php print $target->field_alignment_shortname['und'][0]['value']; ?></h2>
                    <?php print $target->description; ?>
                  </div>
                  <div class="ccss-emphasis">
                    <h3>Emphasis</h3>
                    <h2><?php print $emphasis->field_alignment_shortname['und'][0]['value']; ?></h2>
                    <?php print $emphasis->description; ?>
                 </div>
              <?php endif; ?>
              </div>
            </div>
          </div>

          <?php //print $row['edit_node']; ?>
          <?php //print $row['delete_node']; ?>
          <?php print l('<i class="gen-enclosed foundicon-remove"></i>', '#', array('html' => TRUE, 'attributes' => array('class' => 'ccss-term-delete', 'nid' => $row['nid']))); ?>
        </td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
