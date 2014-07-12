<div
  class="view view-contributed-resources view-id-posted_resource_stats">
  <div class="view-content">
    <table class="views-table cols-8">
      <thead>
      <tr>
        <th class="views-field views-field-title">
          <a href="<?php echo $data['table_title_query']; ?>" title="sort by Title"class="active">Resource Title
          <?php
            if (isset($data['title_image'])) {
              echo $data['title_image'];
            }
          ?>
          </a>
        </th>
        <th class="views-field views-field-created active">
          <a href="<?php echo $data['table_created_query']; ?>" title="sort by Posted Date"class="active">Posted
          <?php
            if (isset($data['created_image'])) {
              echo $data['created_image'];
            }
          ?>
          </a>
        </th>
        <th class="views-field views-field-rating">
          <a href="<?php echo $data['table_rating_query']; ?>" title="sort by Avg. Rating" class="active">Avg. Rating
            <?php
            if (isset($data['rating_image'])) {
              echo $data['rating_image'];
            }
            ?>
          </a>
        </th>
        <th class="views-field views-field-reviewers">
          <a href="<?php echo $data['table_reviewers_query']; ?>" title="sort by Number of Reviewers" class="active">Reviewers
            <?php
            if (isset($data['reviewers_image'])) {
              echo $data['reviewers_image'];
            }
            ?>
          </a>
        </th>
        <th class="views-field views-field-topics">
          <a href="<?php echo $data['table_topics_query']; ?>" title="sort by Number of Topics" class="active">Topics
            <?php
            if (isset($data['topics_image'])) {
              echo $data['topics_image'];
            }
            ?>
          </a>
        </th>
        <th class="views-field views-field-posts">
          <a href="<?php echo $data['table_state_query']; ?>" title="sort by Number of Posts" class="active">Posts
            <?php
            if (isset($data['posts_image'])) {
              echo $data['posts_image'];
            }
            ?>
          </a>
        </th>
        <th class="views-field views-field-downloads">
          <a href="<?php echo $data['table_downloads_query']; ?>" title="sort by Number of Downloads" class="active">Downloads
            <?php
            if (isset($data['downloads_image'])) {
              echo $data['downloads_image'];
            }
            ?>
          </a>
        </th>
        <th class="views-field views-field-views">
          <a href="<?php echo $data['table_views_query']; ?>" title="sort by Number of Views" class="active">Views
            <?php
            if (isset($data['views_image'])) {
              echo $data['views_image'];
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
          echo '<td class="views-field views-field-nid-active">' . $row['title'] . '</td>';
          echo '<td class="views-field views-field-posted">' . $row['posted'] . '</td>';
          echo '<td class="views-field views-field-rating">' . $row['rating'] . '</td>';
          echo '<td class="views-field views-field-reviewers">' . $row['reviewers'] . '</td>';
          echo '<td class="views-field views-field-topics">' . $row['topics'] . '</td>';
          echo '<td class="views-field views-field-posts">' . $row['posts'] . '</td>';
          echo '<td class="views-field views-field-downloads">' . $row['downloads'] . '</td>';
          echo '<td class="views-field views-field-views">' . $row['views'] . '</td>';
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