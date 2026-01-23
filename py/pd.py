# import pandas as pd

# # df = pd.read_csv("address-data-9.csv", header=None,
# #                  names=["prov","city","district","town"])

# df = pd.read_csv("address-data-9.csv")


# print(df[df["prov"] == "湖北省"])
# print(df[df["city"] == "武汉市"])
# print(df[df["district"] == "武昌区"])
# print(df[df["town"] == "积玉桥街道"])

# print(df[df["prov"] == "湖省"].empty)

# d1 = {"1": "1"}
# d2 = {"2": "2", "3": "3"}
# d1.update(d2)
# print(d1)

# df = pd.DataFrame([{
#     "prov": "湖北省",
#     "city": "  武汉市",
#     "district": "武昌区",
#     "town": "积玉桥街道"
# }])

# df.fillna("", inplace=True)
# print(f"df: {df.to_string()}")

import pandas as pd

AREA_LEVELS = ["town", "district", "city", "prov"]

prov_city_district_town_df = pd.read_csv("address-data-9.csv")


def filter_by_col(df: pd.DataFrame, col: str, value: str) -> pd.DataFrame:
    if not value:
        return df
    print(f"col: {col}, value: {value}")
    parts = [v.strip() for v in value.split(";") if v.strip()]
    print(f"parts: {parts}")
    mask = False
    for p in parts:
        mask |= df[col].str.contains(p, na=False)
    # 使用 mask 过滤 df
    return df[mask]


def match_address(row: pd.Series) -> pd.DataFrame:
    """
    从最精确到最粗粒度逐层收缩 df
    """
    cur_df = prov_city_district_town_df

    for level in AREA_LEVELS:
        value = row.get(level)
        if not value:
            continue

        print(f"value: {value}")
        next_df = filter_by_col(cur_df, level, value)

        if next_df.empty:
            continue

        if len(next_df) == 1:
            return next_df

        cur_df = next_df

    return cur_df


def normalize_address_fields(row: pd.Series) -> pd.Series:
    """
    利用 prov_city_district_town_df 内真实字段纠正 first_row
    """
    for src in ["prov", "city", "district", "town"]:
        val = row.get(src)
        if not val:
            continue

        for target in ["town", "district", "city", "prov"]:
            if src == target:
                continue

            if (
                not row.get(target)
                and prov_city_district_town_df[target].str.contains(val, na=False).any()
            ):
                row[target] = val
                row[src] = ""
                break

    return row


"""
# 需要纠正 'prov', 'city', 'district', 'town'
# 传入拆分地址有可能属性有误
# 例如在只有黄冈市时会将黄冈市作为 district，实际为 city
# 需要在 prov_city_district_town_df 中进行纠正
# 421102001,湖北省,黄冈市,黄州区,赤壁街道
# 优先选择 prov_city_district_town_df 内的标签

黄冈麻城市拆分为
city: 黄冈
district: 麻城市
但是字典只存在 '黄冈市'

单独的黄冈市会被拆分成 'district'
因为市有可能是 xx省xx市，也有可能是 xx省xx市xx市

当出现简写的时候，如黄冈市 -> 黄冈
此时查找可能会找到 26924  445122100  广东省  潮州市      饶平县  黄冈镇

"""


def transform_one(first_row: pd.Series) -> pd.DataFrame:
    print(f"raw row:\n{first_row}")

    # 纠正字段错位
    row = normalize_address_fields(first_row.copy())

    print(f"normalized row:\n{row}")

    # 匹配行政区
    result = match_address(row)

    result = result.fillna("")

    print(f"matched result: {result.to_string()}")
    print(f"matched result: {result.shape[0]}")

    return result


if __name__ == "__main__":
    """
    """
    # transform_one(
    #     {
    #         "prov": "",
    #         "city": "",
    #         "district": "武汉",
    #         "town": "",
    #         "village": "",
    #         "community": "21号院",
    #         "communityno": "",
    #         "building_type": "",
    #         "village_group": "",
    #         "devzone": "",
    #         "distance": "",
    #         "intersection": "",
    #         "road": "南大街",
    #         "subroad": "",
    #         "roadno": "",
    #         "houseno": "1号楼",
    #         "cellno": "2单元",
    #         "floorno": "",
    #         "roomno": "201室",
    #         "poi": "",
    #         "subpoi": "",
    #         "detail": "",
    #         "address": "",
    #         "std_label": 0,
    #     }
    # )

    import pandas as pd

    df = pd.DataFrame(
        [
            {
                "prov": "湖北省",
                "city": "  武汉市",
                "district": "武昌区",
                "town": "积玉桥街道",
            },
            {
                "prov": "湖南省",
                "city": "  武汉市",
                "district": "武昌区",
                "town": "积玉桥街道",
            },
        ]
    )
    m = pd.Series(False, index=df.index)
    m |= df["prov"].str.contains("湖北省", na=False)
    m |= df["prov"].str.contains("湖北省", na=False)
    # m |= df["city"].str.contains("武汉市", na=False)
    # m |= df["district"].str.contains("武昌区", na=False)
    # m |= df["town"].str.contains("积玉桥街道", na=False)
    print(m)
