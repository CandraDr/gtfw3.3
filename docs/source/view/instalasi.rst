#########
Instalasi
#########

Instalasi aplikasi berbasis gtfw, pada prinsipnya adalah melakukan copy file-file ke folder
htdoc webserver apache dan melakukan restore file .sql file database ke server mysql, 
untuk kemudian dilakukan konfigurasi agar aplikasi tersebut bisa digunakan.
Ada 3 hal komponen pokok dalam melakukan instalasi aplikasi berbasis gtfw, yaitu:

#. GTFW-Base
#. GTFW-App
#. Database GTFW

.. _instalasi-base:

*********
GTFW-Base
*********

* File-file gtfw-base ini tidak harus diletakkan di bawah folder htdoc dan cukup mengingat lokasi path foldernya, karena di tahapan konfigurasi kita perlu mendefinisikan letak path dari gtfw-base ini.
* Pastikan gtfw-base ini boleh dibase oleh user apache *terutama jika menggunakan linux*.
* Gtfw-base bisa digunakan untuk beberapa aplikasi.
* Gtfw-base bisa di-clone `disini <https://git.solusikampus.id/framework/gtfw-3.3/gtfw-3.3-base>`__.

.. _instalasi-app:

********
GTFW-App
********

* Gtfw-app versi empty adalah source code aplikasi yang masih dasar dan belum kita develop untuk aplikasi tertentu.
* Gtfw-app bisa diletakkan di bawah folder htdoc.
* Gtfw-app versi empty bisa di-clone `disini <https://git.solusikampus.id/framework/gtfw-3.3/gtfw-3.3-app>`__.

*************
Database GTFW
*************

Gtfw-db versi empty adalah file dump .sql dari database yang compatible dengan gtfw-app, 
hanya table-table dasar dan belum ada table untuk aplikasi tertentu.

******
Contoh
******

1. Clone repositori :ref:`GTFW-Base <instalasi-base>` dan :ref:`GTFW-App <instalasi-app>`.
2. Letak clone repositori GTFW-Base bebas dimana saja, sedangkan GTFW-App di dalam folder htdocs.

.. image:: /images/direktori-gtfw.jpg
   :alt: Direktori penempatan GTFW App
   :align: center

.. figure:: /images/struktur-dasar.jpg
   :alt: Struktur dasar direktori GTFW App
   :align: center

   Struktur dasar folder GTFW-App

3. Import file database GTFW ke server mysql. Cth: |img-db-gtfwapp|.
4. Buka folder config/.
5. Copy file **gtfw_base_dir.def.sample** dan pastekan di folder tersebut, kemudian ubah nama file hasil copy paste menjadi **gtfw_base_dir.def**.
6. Buka file gtfw_base_dir.def dengan text editor.
7. Inputkan path folder GTFW-Base yang telah diinstal.

.. image:: /images/path-gtfw-base.jpg
   :alt: Path folder GTFW Base
   :align: center

8. Masih didalam folder config/.
9. Copy file **database.conf.php.sample** dan pastekan di folder tersebut, kemudian ubah nama file hasil copy paste menjadi **database.conf.php**.
10. Buka file **database.conf.php** dengan text editor.
11. Isikan data **db_host**, **db_user**, **db_pass** sesuai konfigurasi server mysql dan **db_name** sesuai nama database GTFW yang sudah di-import.

.. code-block:: php
   :linenos: 
   :caption: Source code @config/database.conf.php

   <?php
   $database['db_conn'][0]['db_driv'] = 'default';
   $database['db_conn'][0]['db_type'] = 'mysqli';
   $database['db_conn'][0]['db_host'] = 'localhost';
   $database['db_conn'][0]['db_user'] = 'root';
   $database['db_conn'][0]['db_pass'] = '';
   $database['db_conn'][0]['db_name'] = 'produk_gtfw33_app';
   $database['db_conn'][0]['db_result_cache_lifetime'] = '';
   $database['db_conn'][0]['db_result_cache_path'] = '';
   $database['db_conn'][0]['db_debug_enabled'] = 'true';
   $database['db_conn'][0]['db_port'] = '3306';
   ?>

.. |img-db-gtfwapp| image:: /images/gtfw-db.jpg
                :alt: Contoh database gtfw