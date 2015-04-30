<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
  flexslider_add();

?>
  <?php if($edit): ?>
  <div id="edit-featured"><?php print $edit;?></div>
<?php endif; ?>
<div id="featured-content-container" class="featured-content-container">
  <?php print $featured_content;?>
</div>
  
  
