/**
 * @file
 * README file for Learning Resource Metadata Initiative.
 */

Learning Resource Metadata Initiative

CONTENTS
--------

1. Introduction
2. Installation
2.1 Requirements
3. Configuration

----
1. Introduction

Learning Resource Metadata Initiative

Extends the Learning Registry module
(http://drupal.org/project/learning_registry). This module allows nodes to be
added to a learning registry node using the Learning Resource Metadata
Initiative (LRMI) schema (http://www.lrmi.net).

----
2. Installation

Install the module and enable it according to Drupal standards.

----
2.1 Requirements

LRMI module requires:
  - Learning Registry 7.x-dev
  - PHP mcrypt extension
  - PHP OAuth extension

----
3. Configuration

After enabling the module, the learning_registry module needs to be configured
to use the LRMI schema (admin/config/services/learning_registry).
