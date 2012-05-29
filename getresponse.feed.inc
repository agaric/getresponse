<?php

/**
 * @file
 * GetResponseRSS Class.
 */

class GetResponseRss {

  /**
   * Functions parse XML data, return string|FALSE.
   */
  protected function parseXMLdata($element_name, $xml, $content_only = TRUE, $match_all = FALSE) {
    if ($xml == FALSE) {
      return FALSE;
    }
    if ($match_all) {
      $found = preg_match_all('#<' . preg_quote($element_name) . '(?:\s+[^>]+)?>' . '(.*?)</' . preg_quote($element_name) . '>#s', $xml, $matches, PREG_PATTERN_ORDER);
    }
    else {
      $found = preg_match('#<' . preg_quote($element_name) . '(?:\s+[^>]+)?>(.*?)' . '</' . preg_quote($element_name) . '>#s', $xml, $matches);
    }
    if ($found != FALSE) {
      if ($content_only) {
        return $matches[1];
      }
      else {
        return $matches[0];
      }
    }
    return FALSE;
  }

  /**
   * Function return RSS data as html string.
   */
  public function renderRss() {
    $result = drupal_http_request(GETRESPONSE_URL_FEED);
    if (!isset($result->error)) {
      $news_items = $this->parseXMLdata('item', $result->data, FALSE, TRUE);
      if (is_array($news_items)) {
        foreach ($news_items as $item) {
          $title = $this->parseXMLdata('title', $item);
          $url = $this->parseXMLdata('link', $item);
          $item_array[] = array(
            'title' => $title,
            'url' => $url,
          );
        }
        $html = '<ul class="GR_rss_ul">';
        $count = 0;
        if (sizeof($news_items) > 0) {
          foreach ($item_array as $item) {
            $html .= '<li class="GR_rss_li">';
            $html .= '<a href="' . check_plain($item['url']) . '" target="_blank">' . $item['title'] . '</a>';
            $html .= '</li>';
            if (++$count == GETRESPONSE_URL_FEED_LIMIT) {
              break;
            }
          }
          $html .= '<ul>';
        }
      }
      else {
        $html = 'No RSS found.';
      }
    }
    else {
      $html = "Can't connect to RSS.";
    }
    return $html;
  }
}
