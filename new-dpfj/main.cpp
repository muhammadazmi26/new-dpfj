#include <iostream>
#include <vector>
#include <string>
#include "base64.h" // Pastikan Anda memiliki implementasi Base64 yang sesuai
#include "dpfj.h"   // Pastikan Anda memiliki library DigitalPersona yang sesuai
#include <libpq-fe.h>
#include <future>
#include <chrono> // Untuk menghitung waktu

#define MY_MAX_FMD_SIZE 2000

using namespace std;
using namespace std::chrono;

using std::cout;
using std::endl;
using std::string;
using std::vector;

bool verifyFingerprint(const string& enrolledFMDBase64, const string& targetFMDBase64)
{
    // Decode Base64 FMDs
    string enrolledFMD = base64_decode(enrolledFMDBase64);
    string targetFMD = base64_decode(targetFMDBase64);

    // FMD Candidate
    unsigned char* enrolledFMDPtr = reinterpret_cast<unsigned char*>(&enrolledFMD[0]);
    unsigned char* targetFMDPtr = reinterpret_cast<unsigned char*>(&targetFMD[0]);

    // Candidates setup
    vector<unsigned char*> candidatesPointers = { enrolledFMDPtr };
    vector<unsigned int> candidatesSize = { static_cast<unsigned int>(enrolledFMD.size()) };

    DPFJ_CANDIDATE matchedCandidatesContainer[1];
    unsigned int expectedMatchesCount = 1;
    unsigned int threshold_score = DPFJ_PROBABILITY_ONE / 1000000;

    // Call the DigitalPersona FMD verify function
    int result = dpfj_identify(
        DPFJ_FMD_DP_VER_FEATURES, // Verification features
        //targetFMDPtr, targetFMD.size(), 0,
        targetFMDPtr, static_cast<unsigned int>(targetFMD.size()), 0,
        DPFJ_FMD_DP_REG_FEATURES, // Registered features
        1,                        // Only one candidate (the enrolled FMD)
        candidatesPointers.data(),
        //candidatesSize.data(),
        reinterpret_cast<unsigned int*>(candidatesSize.data()), // Explicit cast
        threshold_score, // No extra options
        &expectedMatchesCount,
        matchedCandidatesContainer);
    /*cout << "Result: " << result << endl;
    cout << "threshold_score: " << threshold_score << endl;*/

    return (result == DPFJ_SUCCESS && expectedMatchesCount > 0);
}

// int main() {
//     // Sample payload data
//     string enrolledFMDBase64 = "APiAAcgq43NcwEE3CatxcPUUVZJ9uM4u3J4-PSG3TO4rncHL_rU_u5abFuuiuSw7MhXPzFF_gVCmg5XZLhB-l7CN8YOTO0Zqlo3SpCbg2q8El0tkipzkUtt51ji5QW6ujrQ8SyO-A3tkYrT_fYC-9h2tXk0wUihqUFslOfwoOaq9-cdc8qth1VE89LDEPYqWZBV5hhB69Gnjbfxx-ssVEx-Vq-xBycnNC-avVVsiAJzuCMoJitG84lrTmWZlKTZRSoVNGVZzKodwbHX6Ine24vQzr8XwRZbIsHuAtp0QAICTaX56NNES9iDYyOsDL3XZ4oTUrIbym_63uSu6558rpiys_2qf3VKBhvcs9-hiVYq3OyyTiajrjkTIM3gMr8Edml8WqZlXQjx_R1pSiTjK1aFcSijM4T2BRa5aJnSH7TwqkbRa7YIrX1XAErZuZ39m4P0AgTreb3U0v2DuUFLijL9zHESe5rMZ2p7e9R0-7lpPmp1nT-5oY2r5JyuxV9TGNOpGBW8A-H4ByCrjc1zAQTcJq3Gw9BRVkgyIe6Jk4KK7ABIqkZh8MNAgRaon_5ferP-jI9z1vj3zF8-6bQdPjfS3rxB-0q66KfyRHQf4CdjnP4kvkGMgpBh5oPLJXRjDJaGzToBzjW7MRNqLFyqbUyYuHRUjDCsmrcz3BF0lL-Sh-hZmvgmy3fY5gpt9Y-8dfntnUizcRxkUSpZ24BmTvzbU6AvOl-Fqpdz_kscxPfiSi6vdPP2wbIxQYzgsE-K4V0ZhXeWJ0m9M7sH65VLIUz1heswRiv8fzEtvNUxR7bJ3Hiis5ZNrmIjlL7GARuY4KG_eD5uzxB9841YMI2pnUXV47KbYGofII5znbmbfgQYgtuOdpnPhmHBZeMQmCWKzhRKCafs7vrt5b9zSdJm7xmtc1Va24_zC9ihZXzG_vk2OQqZPxchmxy-Gc9VOUImJybzQSsT6c32lZEuyBCALsxodwbkdV_VU0qpIKPmq2RJuK2ufr2j09NjtwNBfY656lJJDI91B5W8A-H8ByCrjc1zAQTcJq3Gw_hRVkoIUdTDCEtOa44QBNTnyXoSC4nbu7T2VgGPyRK41-bjF7Yq4bX-rqAd097AQxqe7wXB9O4sGb74KkMpfbsGiujngWOjD7xwN_m8ba8KDvOk1PxlY5dFsq4AcTVu_aUaof-oarRR3IEP_Ky2HoydTdB4qahUdipuw7c89fpLeNfGWG8-9yqAj9MiYo1wWO8_4I6BcUs6llePgeoYudP8fZk7nzzpO7cD_GOWhg8aArXKqnG6J84XQVtEj2Q75dU9-KF1NIXQdw3THt0m4RZM033vQCvzO_R6pZRMPQtE4wRqv4q8LsxI55nM-Fuz_qMiVPldTo_EfwoLacjLTUAmq8ZQ74VTBDUZqku6dt_1vpC5D9HbGy-va9gbU5t_OvmT2HtJZDIaLhwXeqg1e1dyn9YitTGwFtxokXshs-OlXjX4A6WOtUzOGidEU6g29JXi_TDxUs3FsWVTvwaH4DNweTu-aYSoDThm4u5-sshgzmXZvAOiAAcgq43NcwEE3CatxMOMUVZJ0uzdBRLoUA6WssIasnLnJjDD_RdnI1bBAQS2GEbVnt6Etp_yfbO-Bgk-MFj9WTT1oZT_mKeOMNbybVm_K6n3F42EzX2i_dTQrmfKVrebZvZ9S0MdHtHXzT1OXyW8yE-0Wv5guTeARUec8YWDnw0zyCO-OEbf322tR_csk5cbLXNOeaBFn_WtqEyTUqJ8qEVfYBHAw6t2gX06XJxsM8QMu3Dh5m24QzIzZ4WMNuORd_p43X1YTPKmUrbEZfzovK7lv-2vw51xrl8zjnsEaNertogKurQ2Babl0f2-9KgjC50YcEI5rvwZWp_ABlq0HwD1RYQQa6FasT4h15_avLK47u4eQd5622OWRdQrvM0UXHkQNYzxyb0aALfiHUyi3iYaCVbj0b1WVqGjtl7NunHvp6EkCWnR3T6SACvV6FY2gVhtVrsqLBZFGQsjfl4NE_TMdV89V-cRS16J3JbfYrVbFT1MB36mB0zs2l_1vJx1Fmm9FsIBHfwAAb5cCNhRWAADIHwFwR38AABj7AHBHfwAA4EWwgEd_AAAw-wBwR38AAOBFsIBHfwAAr4IWNhRWAADIHwFwR38AABj7AHBHfwAAcP8AcEd_AAA";
//     string targetFMDBase64 = "AOg5Acgp43NcwEE381mKa_JcZ2YtHmEMxENHZdQBaoC9w4a2KqUMovp1wQeQaDX33IdTKI7BtNH7tN2gLSJQGUgI0ZHJAYcovDs6S2L0HNUNzy9TZiUE8XaXC1tHiJKN-kyk0a0N8GJu-ZKlRFHHLSMWKCSYRaJjurMg4EQSi3FbnxVW-V5a-GGQdmYasIZD-wXwBnqlgVHity0Xm-Vcay--AYaxhVoRnkj6DVkWWPrYc0wYglcj28OiZzR-0xXQT7OZPAoOWk6Puoq9_-fJlodzuZuQtRWiJXIpwQrgYX2jJ5IwUXjx-qz-P9-s-UrHBMj3wd-oonp7KNgLn7Ylp5S1LUtBuAhpX7sjDTJD4MDMbDcR_ZF2sJeanTlUQy2RybEFCdenLIi5slMDVfx27T5nbWCshGb8TFgbaL9v";
//
//     for (size_t i = 0; i < 600; i++)
//     {
//         // Verifikasi
//         if (verifyFingerprint(enrolledFMDBase64, targetFMDBase64)) {
//             cout << "Fingerprint matched!" << endl;
//         }
//         else {
//             cout << "Fingerprint not matched!" << endl;
//         }
//     }
//
//     return 0;
// }

//// Fungsi yang akan dieksekusi paralel
// void verifyTask(const string& enrolledFMDBase64, const string& targetFMDBase64, size_t start, size_t end) {
//     for (size_t i = start; i < end; i++) {
//         if (verifyFingerprint(enrolledFMDBase64, targetFMDBase64)) {
//             //cout << "Fingerprint matched! [" << i << "]" << endl;
//         }
//         else {
//             cout << "Fingerprint not matched! [" << i << "]" << endl;
//         }
//     }
// }
//
// int main() {
//     size_t numTasks = 2;  // Jumlah thread
//     size_t total = 700;   // Total iterasi
//     size_t chunkSize = total / numTasks;
//
//     string enrolledFMDBase64 = "APiAAcgq43NcwEE3CatxcPUUVZJ9uM4u3J4-PSG3TO4rncHL_rU_u5abFuuiuSw7MhXPzFF_gVCmg5XZLhB-l7CN8YOTO0Zqlo3SpCbg2q8El0tkipzkUtt51ji5QW6ujrQ8SyO-A3tkYrT_fYC-9h2tXk0wUihqUFslOfwoOaq9-cdc8qth1VE89LDEPYqWZBV5hhB69Gnjbfxx-ssVEx-Vq-xBycnNC-avVVsiAJzuCMoJitG84lrTmWZlKTZRSoVNGVZzKodwbHX6Ine24vQzr8XwRZbIsHuAtp0QAICTaX56NNES9iDYyOsDL3XZ4oTUrIbym_63uSu6558rpiys_2qf3VKBhvcs9-hiVYq3OyyTiajrjkTIM3gMr8Edml8WqZlXQjx_R1pSiTjK1aFcSijM4T2BRa5aJnSH7TwqkbRa7YIrX1XAErZuZ39m4P0AgTreb3U0v2DuUFLijL9zHESe5rMZ2p7e9R0-7lpPmp1nT-5oY2r5JyuxV9TGNOpGBW8A-H4ByCrjc1zAQTcJq3Gw9BRVkgyIe6Jk4KK7ABIqkZh8MNAgRaon_5ferP-jI9z1vj3zF8-6bQdPjfS3rxB-0q66KfyRHQf4CdjnP4kvkGMgpBh5oPLJXRjDJaGzToBzjW7MRNqLFyqbUyYuHRUjDCsmrcz3BF0lL-Sh-hZmvgmy3fY5gpt9Y-8dfntnUizcRxkUSpZ24BmTvzbU6AvOl-Fqpdz_kscxPfiSi6vdPP2wbIxQYzgsE-K4V0ZhXeWJ0m9M7sH65VLIUz1heswRiv8fzEtvNUxR7bJ3Hiis5ZNrmIjlL7GARuY4KG_eD5uzxB9841YMI2pnUXV47KbYGofII5znbmbfgQYgtuOdpnPhmHBZeMQmCWKzhRKCafs7vrt5b9zSdJm7xmtc1Va24_zC9ihZXzG_vk2OQqZPxchmxy-Gc9VOUImJybzQSsT6c32lZEuyBCALsxodwbkdV_VU0qpIKPmq2RJuK2ufr2j09NjtwNBfY656lJJDI91B5W8A-H8ByCrjc1zAQTcJq3Gw_hRVkoIUdTDCEtOa44QBNTnyXoSC4nbu7T2VgGPyRK41-bjF7Yq4bX-rqAd097AQxqe7wXB9O4sGb74KkMpfbsGiujngWOjD7xwN_m8ba8KDvOk1PxlY5dFsq4AcTVu_aUaof-oarRR3IEP_Ky2HoydTdB4qahUdipuw7c89fpLeNfGWG8-9yqAj9MiYo1wWO8_4I6BcUs6llePgeoYudP8fZk7nzzpO7cD_GOWhg8aArXKqnG6J84XQVtEj2Q75dU9-KF1NIXQdw3THt0m4RZM033vQCvzO_R6pZRMPQtE4wRqv4q8LsxI55nM-Fuz_qMiVPldTo_EfwoLacjLTUAmq8ZQ74VTBDUZqku6dt_1vpC5D9HbGy-va9gbU5t_OvmT2HtJZDIaLhwXeqg1e1dyn9YitTGwFtxokXshs-OlXjX4A6WOtUzOGidEU6g29JXi_TDxUs3FsWVTvwaH4DNweTu-aYSoDThm4u5-sshgzmXZvAOiAAcgq43NcwEE3CatxMOMUVZJ0uzdBRLoUA6WssIasnLnJjDD_RdnI1bBAQS2GEbVnt6Etp_yfbO-Bgk-MFj9WTT1oZT_mKeOMNbybVm_K6n3F42EzX2i_dTQrmfKVrebZvZ9S0MdHtHXzT1OXyW8yE-0Wv5guTeARUec8YWDnw0zyCO-OEbf322tR_csk5cbLXNOeaBFn_WtqEyTUqJ8qEVfYBHAw6t2gX06XJxsM8QMu3Dh5m24QzIzZ4WMNuORd_p43X1YTPKmUrbEZfzovK7lv-2vw51xrl8zjnsEaNertogKurQ2Babl0f2-9KgjC50YcEI5rvwZWp_ABlq0HwD1RYQQa6FasT4h15_avLK47u4eQd5622OWRdQrvM0UXHkQNYzxyb0aALfiHUyi3iYaCVbj0b1WVqGjtl7NunHvp6EkCWnR3T6SACvV6FY2gVhtVrsqLBZFGQsjfl4NE_TMdV89V-cRS16J3JbfYrVbFT1MB36mB0zs2l_1vJx1Fmm9FsIBHfwAAb5cCNhRWAADIHwFwR38AABj7AHBHfwAA4EWwgEd_AAAw-wBwR38AAOBFsIBHfwAAr4IWNhRWAADIHwFwR38AABj7AHBHfwAAcP8AcEd_AAA";
//     string targetFMDBase64 = "AOg5Acgp43NcwEE381mKa_JcZ2YtHmEMxENHZdQBaoC9w4a2KqUMovp1wQeQaDX33IdTKI7BtNH7tN2gLSJQGUgI0ZHJAYcovDs6S2L0HNUNzy9TZiUE8XaXC1tHiJKN-kyk0a0N8GJu-ZKlRFHHLSMWKCSYRaJjurMg4EQSi3FbnxVW-V5a-GGQdmYasIZD-wXwBnqlgVHity0Xm-Vcay--AYaxhVoRnkj6DVkWWPrYc0wYglcj28OiZzR-0xXQT7OZPAoOWk6Puoq9_-fJlodzuZuQtRWiJXIpwQrgYX2jJ5IwUXjx-qz-P9-s-UrHBMj3wd-oonp7KNgLn7Ylp5S1LUtBuAhpX7sjDTJD4MDMbDcR_ZF2sJeanTlUQy2RybEFCdenLIi5slMDVfx27T5nbWCshGb8TFgbaL9v";
//
//
//     vector<future<void>> futures;
//
//     cout << "Verifikasi dimulai!" << endl;
//
//     // Mencatat waktu mulai
//     auto startTime = high_resolution_clock::now();
//     cout << "Start time: " << duration_cast<milliseconds>(startTime.time_since_epoch()).count() << " ms" << endl;
//
//
//     for (size_t t = 0; t < numTasks; ++t) {
//         size_t start = t * chunkSize;
//         size_t end = (t == numTasks - 1) ? total : start + chunkSize;
//         // Menjalankan tugas secara paralel
//         futures.push_back(async(launch::async, verifyTask, enrolledFMDBase64, targetFMDBase64, start, end));
//     }
//
//     // Menunggu semua tugas selesai
//     for (auto& f : futures) {
//         f.get();
//     }
//
//     // Mencatat waktu selesai
//     auto endTime = high_resolution_clock::now();
//     cout << "End time: " << duration_cast<milliseconds>(endTime.time_since_epoch()).count() << " ms" << endl;
//
//     // Menghitung durasi
//     auto duration = duration_cast<milliseconds>(endTime - startTime);
//     cout << "Total waktu eksekusi: " << duration.count() << " ms" << endl;
//
//     cout << "Total iterasi data: " << total << endl;
//
//
//     cout << "Verifikasi selesai!" << endl;
//     return 0;
// }

// Fungsi untuk enroll fingerprint sesuai contoh
string createEnrollment(const vector<string>& fmdCandidates)
{
    if (dpfj_start_enrollment(DPFJ_FMD_DP_REG_FEATURES) != DPFJ_SUCCESS)
    {
        cerr << "Gagal memulai proses enrollment." << endl;
        return "";
    }

    cout << "Jumlah kandidat FMD: " << fmdCandidates.size() << endl;

    for (const string& fmdBase64 : fmdCandidates)
    {
        // Decode base64 ke string biner
        string decodedFMDString = base64_decode(fmdBase64);
        if (decodedFMDString.empty())
            continue;

        // Konversi string biner ke vektor unsigned char dengan aman
        vector<unsigned char> decodedFMD(decodedFMDString.size());
        memcpy(decodedFMD.data(), decodedFMDString.data(), decodedFMDString.size());

        int result = dpfj_add_to_enrollment(
            DPFJ_FMD_DP_PRE_REG_FEATURES,
            decodedFMD.data(),
            //decodedFMD.size(),
            static_cast<unsigned int>(decodedFMD.size()),
            0
        );
        if (result == DPFJ_E_MORE_DATA)
        {
            cout << "Menambahkan FMD kandidat..." << endl;
            continue;
        }
        else if (result != DPFJ_SUCCESS)
        {
            cerr << "Gagal menambahkan kandidat FMD." << endl;
            dpfj_finish_enrollment();
            return "";
        }
    }

    unsigned char regFMD[MY_MAX_FMD_SIZE];
    unsigned int fmdSize = MY_MAX_FMD_SIZE;

    if (dpfj_create_enrollment_fmd(regFMD, &fmdSize) == DPFJ_SUCCESS)
    {
        dpfj_finish_enrollment();
        return string(reinterpret_cast<char*>(regFMD), fmdSize);
    }

    dpfj_finish_enrollment();
    cerr << "Gagal membuat enrollment FMD." << endl;
    return "";
}

// Fungsi paralel untuk verifikasi
int verifyTask(const vector<pair<int, string>>& fingerprints, const string& targetFMDBase64, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        if (verifyFingerprint(fingerprints[i].second, targetFMDBase64))
        {
            return fingerprints[i].first; // Mengembalikan ID siswa
        }
    }
    return -1;
}

int main()
{
    // Koneksi ke database PostgreSQL
    PGconn* conn = PQconnectdb("host=localhost dbname=db_siman user=postgres password=password");
    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Koneksi ke database gagal: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return 1;
    }

    // Membaca data fingerprint dari database
    PGresult* res = PQexec(conn, "SELECT id_student, finger1 FROM m_student_fingerprint ORDER BY id_student ASC LIMIT 1000;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        cerr << "Gagal mengambil data fingerprint: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    // Memuat data ke dalam vector
    vector<pair<int, string>> fingerprints;
    for (int i = 0; i < PQntuples(res); ++i)
    {
        int studentId = stoi(PQgetvalue(res, i, 0));
        string fmdBase64 = PQgetvalue(res, i, 1);
        fingerprints.emplace_back(studentId, fmdBase64);
    }
    PQclear(res);
    PQfinish(conn);

    cout << "Banyak fingerprints didatabase: " << fingerprints.size();

    // Meminta data fingerprint target
    string targetFMDBase64;
    cout << "\nMasukkan fingerprint yang akan diverifikasi: ";
    cin >> targetFMDBase64;

    // Menjalankan verifikasi secara paralel
    size_t numTasks = 2; // Jumlah thread
    size_t chunkSize = fingerprints.size() / numTasks;
    vector<future<int>> futures;

    auto startTime = high_resolution_clock::now();

    for (size_t t = 0; t < numTasks; ++t)
    {
        size_t start = t * chunkSize;
        size_t end = (t == numTasks - 1) ? fingerprints.size() : start + chunkSize;
        futures.push_back(async(launch::async, verifyTask, ref(fingerprints), targetFMDBase64, start, end));
    }

    int matchedId = -1;
    for (auto& f : futures)
    {
        int result = f.get();
        if (result != -1)
        {
            matchedId = result;
            break;
        }
    }

    auto endTime = high_resolution_clock::now();

    // Menampilkan hasil
    if (matchedId != -1)
    {
        cout << "Fingerprint matched! Student ID: " << matchedId << endl;
    }
    else
    {
        cout << "Fingerprint not matched!" << endl;
    }

    auto duration = duration_cast<milliseconds>(endTime - startTime);
    cout << "Total waktu eksekusi: " << duration.count() << " ms" << endl;

    // ENROLL

    vector<string> fmdCandidates = {
        "AOg4Acgp43NcwEE381mKq45cZ2aJCzy_jv63n2djnT1_rYUCXuwlV46rGNfUDFwaLsLwjsTDLnKDHh0_WsXoW-KGDDpKuh3-3mXE30dJxG96qTfaCt41JoKcHu-WjU0j_M0-YHwakNLKUHe4KSIiPNq6hPyVlBTtujNNkmsazj-gZKlksCF2EA3rl1_wDtBI7Q1RWy_m4nJgw8QcYv7txpAKhmuZNwFrIasHpWw1Qf6B6OpV9YDvGr3uzZRvTehHz3GQ-d9uSZTfAcDyykWud_d6zYTLuv_CTqIkayoNGXD_OuoC3bTyOcniupMUdnUmVgSMUtqanvGCN_yzTBZACccZ10uzSq71rXPYrw8upR-CAeUOwYupZNImvJ0T0ZE9BCZq7JaedLs8v9esV0Fcm0t3BkAPUlp9KrIAKW8A",
        "AOg4Acgp43NcwEE381mK65hcZ2YOZXPHpBDcxnmqVJg7vyjG18W_UtnM2orW0U_ykdsOybm8rdHil5uiuTggR6oFgL5j_sFLvhWVyWTkr2f_3WbZXwSPdd3PTq1uSdR3fjCPXf_3xdqL9PviyhZPezsuC_Oh-AsQKR3bZ7xSMHdL3n0sd1KoBF5zBLt3bR2TeH1v14DIG2NlV5fWKthVAhpGRn2H5398rvgXWzyBtH6nCwrabl6wRbNYz0A8epr4xF8GMBtF523n66w4PKBFBEJTEUwyGN0aPLuxko7wyA1rnoWwOokKErWMy8dh51ZHnUm4bjn3VgBh08SgQxODClGLvHPO31D0UKoONbHHT-khnalc1pGuhb3nU5d7T8fw-SDTa8rBvHl8izfq5VHfqyNVaxQHn82spXyc5G8A",
        "AOg3Acgp43NcwEE381mKK5NcZ2bSlsRy87zYu2XZa-7U9-8LgPqyQJFYUNt2x0-C8afEfKYu2jvMSKaUHTNc4In0QzT5RFx0OpbYxOxcHrEuj3etxNhBb5jxtYdtPJOMFSoIPpkLJvEFsrWAGB3942_c7qoKdYCkziHNQ6iS9E8tUkzmFlUdpG1PtPQqPVpSDE7P5D12wnuQNO6rnS-T3HhQjzO5EHi0bToD4x5zlrzFiwfl92nYbiU6gW3Tq6iklkSxQ3eZh7Q6qH-VUKy82_j2S_YsFZpN0a3nBp1gYUTmH6DiIpoflhfSw-5gYl15dR17lqLVEA-nChPUFeLhs-ZE_IIlJ7pBmDvmjSjvOQfPf50on7_nrytWzke9-wLPK2RPwhgiIifSOB8xtR89zMc4B5B9zeHDC3h3bwAA",
        "AOg2Acgp43NcwEE381mKK5lcZ2bfPoP6aDUhn7eVf-jylUG7p6R3SlA4PTKrztYeFLaHRwOjnBItq-MYek1E7dX8_P9PJ8x-XKCh2v5WI_rzYz8BP2ntVX1Simt8bGj-ZgDYJqB2fObmVFC0d4524oShAxTl92gtNd44Z4a8pax2XAd6NVr3XdHBJnTJ0bzw_WWIR-n-GH8ffM4U7iTfeaS1TUFDbttFn17lvEYI0LIagGuwaSUUTRd3zeF8QCl6a9WqldvIDI2G_IINbuXIigRCepbtTpSmQ88rMdF3ZwNqMWKeNJmBfwsWELgUvqMWZeR78VLlKk-aWHUKwc1SpmM_8RUQSeaHFIcbnK2iaosQJyLZOyOyrJMrlAG3RZ-35IT5gRRMUQHm6CUbxSegFEIzcVwWqurJpndvAAAA" };

    string enrolledFMD = createEnrollment(fmdCandidates);
    if (!enrolledFMD.empty())
    {
        cout << "Hasil Enrollment (Base64): " << base64_encode(enrolledFMD) << endl;
    }
    else
    {
        cout << "Enrollment gagal." << endl;
    }

    return 0;
}
