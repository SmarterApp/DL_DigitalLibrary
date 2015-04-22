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
        elseif ($is_ma = ($subject->name == 'Mathematics')) {
           $grade = array_pop($parents);
           $claim = array_pop($parents);
        }
        else {
           //do nothing
        }
      ?>

      <tr id="term-<?php print $row['nid']; ?>">
        <td><?php print $tag_node->field_alignment_shortname['und'][0]['value']; ?></td>
        <!--<td><?php print $row['field_education_alignment']; ?></td>-->
<!--        <td>--><?php //print $row['field_alignment_type']; ?><!--</td>-->
        <td>
          <div class="read-more">
            <a href="#" title="Read More" class=""><i class="accessibility foundicon-eyeball"></i><span>Read More</span></a>
            <div class="more description-hover">
              <div class="description-content">
              <h2><?php print $subject->name; ?></h2>
              <div class="ccss-standard">
                <h3>CCSS</h3>
                 <h2><?php print $tag_node->field_alignment_shortname['und'][0]['value']; ?></h2>
                 <?php print $tag_node->description; ?>
              </div>
              <div class="ccss-grade">
                <h3>Grade</h3>
                <?php
                  if (isset($grade)) {
                    $pos = strpos($grade->name, ':');
                    if ($pos !== FALSE) {
                      $new_name = substr($grade->name, $pos + 1);
                      $grade->name = trim($new_name);
                    }
                    print $grade->name;
                  }
                ?>
              </div>
              <div class="ccss-claim">
                <?php if ($is_ela) : ?>
                  <h3>Strands/Domain</h3>
                <?php endif; ?>
                <?php if ($is_ma) : ?>
                  <h3>Domain</h3>
                <?php endif; ?>
                <?php if (isset($claim)): ?>
                  <?php print $claim->field_alignment_shortname['und'][0]['value']; ?>
                <?php endif; ?>
              </div>
              </div>
            </div>
          </div>
          <?php print l('<i class="gen-enclosed foundicon-remove"></i><span>Remove</span>', '#', array('html' => TRUE, 'attributes' => array('title' => 'Remove', 'class' => 'ccss-term-delete', 'nid' => $row['nid']))); ?>
        </td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
