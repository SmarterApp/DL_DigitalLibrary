<div class="row">
  <div class="columns large-12">
    <h1>Welcome to the Smarter Balanced Digital Library</h1>
    <p> The Digital Library is an online, user-friendly, searchable library for educators that contains only high-quality vetted resources. It is interactive and allows educators from member states to use and rate resources and to collaborate.</p>
  </div>
</div>
<div class="row">
  <div class="columns small-12 large-8 login-text">
    <ul>
      <li class="top">
        <i class="enclosed foundicon-website"></i>
        <div class="big"><?php print render($left_top_big); ?></div>
        <div class="small"><?php print render($left_top_small); ?></div>
      </li>
      <li class="middle">
        <i class="enclosed foundicon-edit"></i>
        <div class="big"><?php print render($left_middle_big); ?></div>
        <div class="small"><?php print render($left_middle_small); ?></div>
      </li>
      <li class="bottom">
        <i class="accessibility foundicon-question"></i>
        <div class="big"><?php print render($left_bottom_big); ?></div>
        <div class="small"><?php print render($left_bottom_small); ?></div></li>
    </ul>
  </div>
  <div class="columns small-12 large-4 sbac-user-login-form-wrapper">
    <?php print drupal_render_children($form) ?>
  </div>
</div>
