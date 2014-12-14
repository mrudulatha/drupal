INTRODUCTION
------------

The Node Clone mapping module builds mapping between different nodes cloned and
copies comments between cloned nodes.

REQUIREMENTS
------------
This module requires the following modules:

* Node Clone (https://www.drupal.org/project/node_clone)

INSTALLATION
------------

* Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.

CONFIGURATION
-------------

* Configure user permissions in Administration » People » Permissions:

   - Administer node clone mapping

     Users in roles with the "Administer node clone mapping" permission 
	 will see the administration page to manage nodes mapping and 
	 to copy comments of the nodes.

* Navigate to "admin/config/content/mapping" for enabling the clone 
  mapping for content types and settings to copy comments between cloned nodes.
