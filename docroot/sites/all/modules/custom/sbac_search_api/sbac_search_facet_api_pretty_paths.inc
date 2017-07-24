<?php

/**
 * @file
 * A modified taxonomy specific coder for pretty paths.
 */

/**
 * Taxonomy specific implementation of FacetApiPrettyPathsCoder.
 */
class SBACFacetApiPrettyPathsCoderTaxonomy extends FacetApiPrettyPathsCoderDefault {

  /**
   * Taxonomy special case: <alias>/<term-name>-<term-id>
   *
   * @see FacetApiPrettyPathsCoderDefault::encodePathSegment()
   */
  public function encodePathSegment(array $args) {
    return parent::encodePathSegment($args);
  }

  /**
   * Taxonomy special case: <alias>/<term-name>-<term-id>
   *
   * @see FacetApiPrettyPathsCoderDefault::decodePathSegmentValue()
   */
  public function decodePathSegmentValue(array $args) {
    return parent::decodePathSegmentValue($args);
  }
}
