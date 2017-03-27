<?php
/**
 * @file
 * Template for SBAC Resource Report Summaries.
 */
?>
<h1>Results Summary</h1>
<?php foreach ($resource_output as $resource): ?>
  <?php
    $grades_array = explode(',', $resource['contributor']['grades']);
    $grades = '';
    foreach ($grades_array as $grade) {
      $grades .= '<span class="attribute">' . $grade . '</span>';
    }
    $subjects_array = explode(',', $resource['contributor']['subjects']);
    $subjects = '';
    foreach ($subjects_array as $subject) {
      $subjects .= '<span class="attribute">' . $subject . '</span>';
    }
    $populations_array = explode(',', $resource['contributor']['populations']);
    $populations = '';
    foreach ($populations_array as $population) {
      $populations .= '<span class="attribute">' . $population . '</span>';
    }
    $roles_array = explode(',', $resource['contributor']['roles']);
    $roles = '';
    foreach ($roles_array as $role) {
      $roles .= '<span class="attribute">' . $role . '</span>';
    }
  ?>
  <h2><?php print $resource['title']['title']; ?></h2>
  <table class="results-summary">
    <tr><th>Resource Information</th><th></th></tr>
    <tr>
      <td>URL</td>
      <td><a href="<?php print $resource['title']['url']; ?>"><?php print $resource['title']['url']; ?></a></td>
    </tr>
    <tr>
      <td>Creation Date</td>
      <td><?php print $resource['title']['creation_date']; ?></td>
    </tr>
    <tr>
      <td>Status</td>
      <td><?php print $resource['title']['status']; ?></td>
    </tr>
  </table>
  <table class="results-summary">
    <tr><th>Contributor Information</th><th></th></tr>
    <tr>
      <td>Contributor Name</td>
      <td><?php print $resource['contributor']['name']; ?></td>
    </tr>
    <tr>
      <td>Contributor Email Address</td>
      <td><?php $resource['contributor']['email'] ? print $resource['contributor']['email'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Contributor Title</td>
      <td><?php $resource['contributor'][2] ? print $resource['contributor']['title'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Contributor State</td>
      <td><?php $resource['contributor']['state'] ? print $resource['contributor']['state'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Contributor District</td>
      <td><?php $resource['contributor']['district'] ? print $resource['contributor']['district'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Contributor Grades</td>
      <td><?php $grades ? print $grades : print '-'; ?></td>
    </tr>
    <tr>
      <td>Contributor Subjects</td>
      <td><?php $subjects ? print $subjects : print '-'; ?></td>
    </tr>
    <tr>
      <td>Contributor Roles</td>
      <td><?php $roles ? print $roles : print '-'; ?></td>
    </tr>
  </table>
  <table class="results-summary">
    <tr><th>Resource Statistics</th><th></th></tr>
    <tr>
      <td>Views</td>
      <td><?php $resource['stats']['views'] ? print $resource['stats']['views'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Unique Views</td>
      <td><?php $resource['stats']['unique_views'] ? print $resource['stats']['unique_views'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Downloads</td>
      <td><?php $resource['stats']['downloads'] ? print $resource['stats']['downloads'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Unique Downloads</td>
      <td><?php $resource['stats']['unique_downloads'] ? print $resource['stats']['unique_downloads'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Current Student Learning Rating</td>
      <td><?php $resource['stats']['sl_rating'] ? print $resource['stats']['sl_rating'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Current Professional Development Rating</td>
      <td><?php $resource['stats']['pd_rating'] ? print $resource['stats']['pd_rating'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Current Ease of Use Rating</td>
      <td><?php $resource['stats']['eou_rating'] ? print $resource['stats']['eou_rating'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Current Top Three “Appropriate For” Rating</td>
      <td><?php $resource['stats']['top_three_rating'] ? print $resource['stats']['top_three_rating'] : print '-'; ?></td>
    </tr>
    <tr>
      <td>Total Number of Ratings</td>
      <td><?php $resource['stats']['total_rating'] ? print $resource['stats']['total_rating'] : print '-'; ?></td>
    </tr>
  </table>
<?php endforeach; ?>