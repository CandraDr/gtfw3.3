#########
Instalasi
#########

Instalasi aplikasi berbasis gtfw, pada prinsipnya adalah melakukan copy file-file ke folder
htdoc webserver apache dan melakukan restore file .sql file database ke server mysql, 
untuk kemudian dilakukan konfigurasi agar aplikasi tersebut bisa digunakan.
Ada 3 hal komponen pokok dalam melakukan instalasi aplikasi berbasis gtfw, yaitu:

1. GTFW-Base
2. GTFW-App
3. Database GTFW

.. _base:

*********
GTFW-Base
*********

* File-file gtfw-base ini tidak harus diletakkan di bawah folder htdoc dan cukup mengingat lokasi path foldernya, karena di tahapan konfigurasi kita perlu mendefinisikan letak path dari gtfw-base ini.
* Pastikan gtfw-base ini boleh dibase oleh user apache *terutama jika menggunakan linux*.
* Gtfw-base bisa digunakan untuk beberapa aplikasi.
* Gtfw-base bisa di-clone `disini <https://git.solusikampus.id/framework/gtfw-3.3/gtfw-3.3-base>`__.

.. _app:

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

1. Clone repositori :ref:`GTFW-Base <base>` dan :ref:`GTFW-App <app>`.
2. Letak clone repositori GTFW-Base bebas dimana saja, sedangkan GTFW-App di dalam folder htdocs.

.. image:: /images/direktori-gtfw.jpg
   :alt: Direktori penempatan GTFW App
   :align: center

3. Struktur dasar folder GTFW-App:

.. image:: /images/struktur-dasar.jpg
   :alt: Struktur dasar direktori GTFW App
   :align: center

4. Import file database GTFW ke server mysql. Cth: |db-gtfwapp|.
5. Buka folder config/.
6. Copy file **gtfw_base_dir.def.sample** dan pastekan di folder tersebut, kemudian ubah nama file hasil copy paste menjadi **gtfw_base_dir.def**.
7. Buka file gtfw_base_dir.def dengan text editor.
8. Inputkan path folder GTFW-Base yang telah diinstal.

.. image:: /images/path-gtfw-base.jpg
   :alt: Path folder GTFW Base
   :align: center

9. Masih didalam folder config/.
10. Copy file **database.conf.php.sample** dan pastekan di folder tersebut, kemudian ubah nama file hasil copy paste menjadi **database.conf.php**.
11. Buka file **database.conf.php** dengan text editor.
12. Isikan data **db_host**, **db_user**, **db_pass** sesuai konfigurasi server mysql dan **db_name** sesuai nama database GTFW yang sudah di-import.

.. code-block:: php

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


.. |db-gtfwapp| image:: /images/gtfw-db.jpg
                :alt: Contoh database gtfw