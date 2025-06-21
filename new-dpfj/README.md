######################################################### PERSIAPAN #################################################

# Environment
  - Windows 10
  - Visual studio 2022
  - Postgresql 16 (terinstal di C:\Program Files\PostgreSQL\16)
  - Digital persona 4500 (terinstal di C:\Program Files\DigitalPersona\SDK)


# Cara setup
 - Buka project di visual studio 2022

 - Klik kanan project di Solution Explorer
   Add → Existing Item
   Pilih base64.h dan base64.cpp

 - Set Include Directories
   Klik kanan, lalu klik Properties → C/C++ → General → Additional Include Directories
   Tambahkan path ke folder include: 1. C:\Program Files\DigitalPersona\SDK\include (Digital persona)
									 2. C:\Program Files\PostgreSQL\16\include (PostgreSQL)

 - Set Library Directories
   Project Properties → Linker → General → Additional Library Directories
   Tambahkan path ke folder lib: 1. C:\Program Files\DigitalPersona\SDK\lib\x64 (Digital persona)
								 2. C:\Program Files\PostgreSQL\16\lib (PostgreSQL)

 - Di Linker → Input → Additional Dependencies, tambahkan text berikut:
   libpq.lib
   dpfj.lib

 - jangan lupa apply jika sudah selesai, agar settingan tersimpan.


# Cara jalankan
	- Tekan CTRL + B untuk build
    - Tekan F5 untuk run atau CTRL + F5 untuk run tanpa debug


##################################################### SAMPLE DATA #########################################################

# sample data enroll (4 data untuk satu jari). digunkan untuk melakukan enroll atau register sidikjari.
  fmdCandidates = {
        "AOg4Acgp43NcwEE381mKq45cZ2aJCzy_jv63n2djnT1_rYUCXuwlV46rGNfUDFwaLsLwjsTDLnKDHh0_WsXoW-KGDDpKuh3-3mXE30dJxG96qTfaCt41JoKcHu-WjU0j_M0-YHwakNLKUHe4KSIiPNq6hPyVlBTtujNNkmsazj-gZKlksCF2EA3rl1_wDtBI7Q1RWy_m4nJgw8QcYv7txpAKhmuZNwFrIasHpWw1Qf6B6OpV9YDvGr3uzZRvTehHz3GQ-d9uSZTfAcDyykWud_d6zYTLuv_CTqIkayoNGXD_OuoC3bTyOcniupMUdnUmVgSMUtqanvGCN_yzTBZACccZ10uzSq71rXPYrw8upR-CAeUOwYupZNImvJ0T0ZE9BCZq7JaedLs8v9esV0Fcm0t3BkAPUlp9KrIAKW8A",
        "AOg4Acgp43NcwEE381mK65hcZ2YOZXPHpBDcxnmqVJg7vyjG18W_UtnM2orW0U_ykdsOybm8rdHil5uiuTggR6oFgL5j_sFLvhWVyWTkr2f_3WbZXwSPdd3PTq1uSdR3fjCPXf_3xdqL9PviyhZPezsuC_Oh-AsQKR3bZ7xSMHdL3n0sd1KoBF5zBLt3bR2TeH1v14DIG2NlV5fWKthVAhpGRn2H5398rvgXWzyBtH6nCwrabl6wRbNYz0A8epr4xF8GMBtF523n66w4PKBFBEJTEUwyGN0aPLuxko7wyA1rnoWwOokKErWMy8dh51ZHnUm4bjn3VgBh08SgQxODClGLvHPO31D0UKoONbHHT-khnalc1pGuhb3nU5d7T8fw-SDTa8rBvHl8izfq5VHfqyNVaxQHn82spXyc5G8A",
        "AOg3Acgp43NcwEE381mKK5NcZ2bSlsRy87zYu2XZa-7U9-8LgPqyQJFYUNt2x0-C8afEfKYu2jvMSKaUHTNc4In0QzT5RFx0OpbYxOxcHrEuj3etxNhBb5jxtYdtPJOMFSoIPpkLJvEFsrWAGB3942_c7qoKdYCkziHNQ6iS9E8tUkzmFlUdpG1PtPQqPVpSDE7P5D12wnuQNO6rnS-T3HhQjzO5EHi0bToD4x5zlrzFiwfl92nYbiU6gW3Tq6iklkSxQ3eZh7Q6qH-VUKy82_j2S_YsFZpN0a3nBp1gYUTmH6DiIpoflhfSw-5gYl15dR17lqLVEA-nChPUFeLhs-ZE_IIlJ7pBmDvmjSjvOQfPf50on7_nrytWzke9-wLPK2RPwhgiIifSOB8xtR89zMc4B5B9zeHDC3h3bwAA",
        "AOg2Acgp43NcwEE381mKK5lcZ2bfPoP6aDUhn7eVf-jylUG7p6R3SlA4PTKrztYeFLaHRwOjnBItq-MYek1E7dX8_P9PJ8x-XKCh2v5WI_rzYz8BP2ntVX1Simt8bGj-ZgDYJqB2fObmVFC0d4524oShAxTl92gtNd44Z4a8pax2XAd6NVr3XdHBJnTJ0bzw_WWIR-n-GH8ffM4U7iTfeaS1TUFDbttFn17lvEYI0LIagGuwaSUUTRd3zeF8QCl6a9WqldvIDI2G_IINbuXIigRCepbtTpSmQ88rMdF3ZwNqMWKeNJmBfwsWELgUvqMWZeR78VLlKk-aWHUKwc1SpmM_8RUQSeaHFIcbnK2iaosQJyLZOyOyrJMrlAG3RZ-35IT5gRRMUQHm6CUbxSegFEIzcVwWqurJpndvAAAA" 
  };


# sample data hasil enroll (1 data). ini didapatkan dari proses enroll atau register. data inilah yg disimpan ke database untuk proses verify nantinya.
  hasilEnrollment (Base64): "APiAAcgq43NcwEE3CatxcPUUVZJ9uM4u3J4-PSG3TO4rncHL_rU_u5abFuuiuSw7MhXPzFF_gVCmg5XZLhB-l7CN8YOTO0Zqlo3SpCbg2q8El0tkipzkUtt51ji5QW6ujrQ8SyO-A3tkYrT_fYC-9h2tXk0wUihqUFslOfwoOaq9-cdc8qth1VE89LDEPYqWZBV5hhB69Gnjbfxx-ssVEx-Vq-xBycnNC-avVVsiAJzuCMoJitG84lrTmWZlKTZRSoVNGVZzKodwbHX6Ine24vQzr8XwRZbIsHuAtp0QAICTaX56NNES9iDYyOsDL3XZ4oTUrIbym_63uSu6558rpiys_2qf3VKBhvcs9-hiVYq3OyyTiajrjkTIM3gMr8Edml8WqZlXQjx_R1pSiTjK1aFcSijM4T2BRa5aJnSH7TwqkbRa7YIrX1XAErZuZ39m4P0AgTreb3U0v2DuUFLijL9zHESe5rMZ2p7e9R0-7lpPmp1nT-5oY2r5JyuxV9TGNOpGBW8A-H4ByCrjc1zAQTcJq3Gw9BRVkgyIe6Jk4KK7ABIqkZh8MNAgRaon_5ferP-jI9z1vj3zF8-6bQdPjfS3rxB-0q66KfyRHQf4CdjnP4kvkGMgpBh5oPLJXRjDJaGzToBzjW7MRNqLFyqbUyYuHRUjDCsmrcz3BF0lL-Sh-hZmvgmy3fY5gpt9Y-8dfntnUizcRxkUSpZ24BmTvzbU6AvOl-Fqpdz_kscxPfiSi6vdPP2wbIxQYzgsE-K4V0ZhXeWJ0m9M7sH65VLIUz1heswRiv8fzEtvNUxR7bJ3Hiis5ZNrmIjlL7GARuY4KG_eD5uzxB9841YMI2pnUXV47KbYGofII5znbmbfgQYgtuOdpnPhmHBZeMQmCWKzhRKCafs7vrt5b9zSdJm7xmtc1Va24_zC9ihZXzG_vk2OQqZPxchmxy-Gc9VOUImJybzQSsT6c32lZEuyBCALsxodwbkdV_VU0qpIKPmq2RJuK2ufr2j09NjtwNBfY656lJJDI91B5W8A-H8ByCrjc1zAQTcJq3Gw_hRVkoIUdTDCEtOa44QBNTnyXoSC4nbu7T2VgGPyRK41-bjF7Yq4bX-rqAd097AQxqe7wXB9O4sGb74KkMpfbsGiujngWOjD7xwN_m8ba8KDvOk1PxlY5dFsq4AcTVu_aUaof-oarRR3IEP_Ky2HoydTdB4qahUdipuw7c89fpLeNfGWG8-9yqAj9MiYo1wWO8_4I6BcUs6llePgeoYudP8fZk7nzzpO7cD_GOWhg8aArXKqnG6J84XQVtEj2Q75dU9-KF1NIXQdw3THt0m4RZM033vQCvzO_R6pZRMPQtE4wRqv4q8LsxI55nM-Fuz_qMiVPldTo_EfwoLacjLTUAmq8ZQ74VTBDUZqku6dt_1vpC5D9HbGy-va9gbU5t_OvmT2HtJZDIaLhwXeqg1e1dyn9YitTGwFtxokXshs-OlXjX4A6WOtUzOGidEU6g29JXi_TDxUs3FsWVTvwaH4DNweTu-aYSoDThm4u5-sshgzmXZvAOiAAcgq43NcwEE3CatxMOMUVZJ0uzdBRLoUA6WssIasnLnJjDD_RdnI1bBAQS2GEbVnt6Etp_yfbO-Bgk-MFj9WTT1oZT_mKeOMNbybVm_K6n3F42EzX2i_dTQrmfKVrebZvZ9S0MdHtHXzT1OXyW8yE-0Wv5guTeARUec8YWDnw0zyCO-OEbf322tR_csk5cbLXNOeaBFn_WtqEyTUqJ8qEVfYBHAw6t2gX06XJxsM8QMu3Dh5m24QzIzZ4WMNuORd_p43X1YTPKmUrbEZfzovK7lv-2vw51xrl8zjnsEaNertogKurQ2Babl0f2-9KgjC50YcEI5rvwZWp_ABlq0HwD1RYQQa6FasT4h15_avLK47u4eQd5622OWRdQrvM0UXHkQNYzxyb0aALfiHUyi3iYaCVbj0b1WVqGjtl7NunHvp6EkCWnR3T6SACvV6FY2gVhtVrsqLBZFGQsjfl4NE_TMdV89V-cRS16J3JbfYrVbFT1MB36mB0zs2l_1vJx1Fmm_MzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMw"


 # sample data untuk verify (1 data). digunakan untuk proses verify. data ini akan dicocokkan dengan data pada database
  dataVerify = "AOg5Acgp43NcwEE381mKa_JcZ2YtHmEMxENHZdQBaoC9w4a2KqUMovp1wQeQaDX33IdTKI7BtNH7tN2gLSJQGUgI0ZHJAYcovDs6S2L0HNUNzy9TZiUE8XaXC1tHiJKN-kyk0a0N8GJu-ZKlRFHHLSMWKCSYRaJjurMg4EQSi3FbnxVW-V5a-GGQdmYasIZD-wXwBnqlgVHity0Xm-Vcay--AYaxhVoRnkj6DVkWWPrYc0wYglcj28OiZzR-0xXQT7OZPAoOWk6Puoq9_-fJlodzuZuQtRWiJXIpwQrgYX2jJ5IwUXjx-qz-P9-s-UrHBMj3wd-oonp7KNgLn7Ylp5S1LUtBuAhpX7sjDTJD4MDMbDcR_ZF2sJeanTlUQy2RybEFCdenLIi5slMDVfx27T5nbWCshGb8TFgbaL9v";


########################################################## UJI COBA ########################################################

- jalankan seperti panduan diatas, lalu kan muncul terminal untuk masukkan data sidik jari. masukkan contoh data "sample data untuk verify" diatas."
- jika berhasil, akan muncul output seperti ini:
    ```
    [+] Banyak fingerprints didatabase: 700
    [+] Masukkan fingerprint yang akan diverifikasi: AOg5Acgp43NcwEE381mKa_JcZ2YtHmEMxENHZdQBaoC9w4a2KqUMovp1wQeQaDX33IdTKI7BtNH7tN2gLSJQGUgI0ZHJAYcovDs6S2L0HNUNzy9TZiUE8XaXC1tHiJKN-kyk0a0N8GJu-ZKlRFHHLSMWKCSYRaJjurMg4EQSi3FbnxVW-V5a-GGQdmYasIZD-wXwBnqlgVHity0Xm-Vcay--AYaxhVoRnkj6DVkWWPrYc0wYglcj28OiZzR-0xXQT7OZPAoOWk6Puoq9_-fJlodzuZuQtRWiJXIpwQrgYX2jJ5IwUXjx-qz-P9-s-UrHBMj3wd-oonp7KNgLn7Ylp5S1LUtBuAhpX7sjDTJD4MDMbDcR_ZF2sJeanTlUQy2RybEFCdenLIi5slMDVfx27T5nbWCshGb8TFgbaL9v
    [+] Fingerprint matched! Student ID: 699
    [+] Total waktu eksekusi: 1571 ms
    [+] Jumlah kandidat FMD: 4
    [+] Menambahkan FMD kandidat...
    [+] Menambahkan FMD kandidat...
    [+] Menambahkan FMD kandidat...
    [+] Hasil Enrollment (Base64): APiAAcgq43NcwEE3CatxcPUUVZJ9uM4u3J4-PSG3TO4rncHL_rU_u5abFuuiuSw7MhXPzFF_gVCmg5XZLhB-l7CN8YOTO0Zqlo3SpCbg2q8El0tkipzkUtt51ji5QW6ujrQ8SyO-A3tkYrT_fYC-9h2tXk0wUihqUFslOfwoOaq9-cdc8qth1VE89LDEPYqWZBV5hhB69Gnjbfxx-ssVEx-Vq-xBycnNC-avVVsiAJzuCMoJitG84lrTmWZlKTZRSoVNGVZzKodwbHX6Ine24vQzr8XwRZbIsHuAtp0QAICTaX56NNES9iDYyOsDL3XZ4oTUrIbym_63uSu6558rpiys_2qf3VKBhvcs9-hiVYq3OyyTiajrjkTIM3gMr8Edml8WqZlXQjx_R1pSiTjK1aFcSijM4T2BRa5aJnSH7TwqkbRa7YIrX1XAErZuZ39m4P0AgTreb3U0v2DuUFLijL9zHESe5rMZ2p7e9R0-7lpPmp1nT-5oY2r5JyuxV9TGNOpGBW8A-H4ByCrjc1zAQTcJq3Gw9BRVkgyIe6Jk4KK7ABIqkZh8MNAgRaon_5ferP-jI9z1vj3zF8-6bQdPjfS3rxB-0q66KfyRHQf4CdjnP4kvkGMgpBh5oPLJXRjDJaGzToBzjW7MRNqLFyqbUyYuHRUjDCsmrcz3BF0lL-Sh-hZmvgmy3fY5gpt9Y-8dfntnUizcRxkUSpZ24BmTvzbU6AvOl-Fqpdz_kscxPfiSi6vdPP2wbIxQYzgsE-K4V0ZhXeWJ0m9M7sH65VLIUz1heswRiv8fzEtvNUxR7bJ3Hiis5ZNrmIjlL7GARuY4KG_eD5uzxB9841YMI2pnUXV47KbYGofII5znbmbfgQYgtuOdpnPhmHBZeMQmCWKzhRKCafs7vrt5b9zSdJm7xmtc1Va24_zC9ihZXzG_vk2OQqZPxchmxy-Gc9VOUImJybzQSsT6c32lZEuyBCALsxodwbkdV_VU0qpIKPmq2RJuK2ufr2j09NjtwNBfY656lJJDI91B5W8A-H8ByCrjc1zAQTcJq3Gw_hRVkoIUdTDCEtOa44QBNTnyXoSC4nbu7T2VgGPyRK41-bjF7Yq4bX-rqAd097AQxqe7wXB9O4sGb74KkMpfbsGiujngWOjD7xwN_m8ba8KDvOk1PxlY5dFsq4AcTVu_aUaof-oarRR3IEP_Ky2HoydTdB4qahUdipuw7c89fpLeNfGWG8-9yqAj9MiYo1wWO8_4I6BcUs6llePgeoYudP8fZk7nzzpO7cD_GOWhg8aArXKqnG6J84XQVtEj2Q75dU9-KF1NIXQdw3THt0m4RZM033vQCvzO_R6pZRMPQtE4wRqv4q8LsxI55nM-Fuz_qMiVPldTo_EfwoLacjLTUAmq8ZQ74VTBDUZqku6dt_1vpC5D9HbGy-va9gbU5t_OvmT2HtJZDIaLhwXeqg1e1dyn9YitTGwFtxokXshs-OlXjX4A6WOtUzOGidEU6g29JXi_TDxUs3FsWVTvwaH4DNweTu-aYSoDThm4u5-sshgzmXZvAOiAAcgq43NcwEE3CatxMOMUVZJ0uzdBRLoUA6WssIasnLnJjDD_RdnI1bBAQS2GEbVnt6Etp_yfbO-Bgk-MFj9WTT1oZT_mKeOMNbybVm_K6n3F42EzX2i_dTQrmfKVrebZvZ9S0MdHtHXzT1OXyW8yE-0Wv5guTeARUec8YWDnw0zyCO-OEbf322tR_csk5cbLXNOeaBFn_WtqEyTUqJ8qEVfYBHAw6t2gX06XJxsM8QMu3Dh5m24QzIzZ4WMNuORd_p43X1YTPKmUrbEZfzovK7lv-2vw51xrl8zjnsEaNertogKurQ2Babl0f2-9KgjC50YcEI5rvwZWp_ABlq0HwD1RYQQa6FasT4h15_avLK47u4eQd5622OWRdQrvM0UXHkQNYzxyb0aALfiHUyi3iYaCVbj0b1WVqGjtl7NunHvp6EkCWnR3T6SACvV6FY2gVhtVrsqLBZFGQsjfl4NE_TMdV89V-cRS16J3JbfYrVbFT1MB36mB0zs2l_1vJx1Fmm_MzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMzMw
    [+] C:\Users\Muhammad Azmi\Source\Repos\new-dpfj\x64\Debug\new-dpfj.exe (process 24968) exited with code 0 (0x0).
    [+] To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
    [+] Press any key to close this window . . .
    ```