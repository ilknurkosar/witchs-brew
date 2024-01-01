target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_sources(${PROJECT_NAME} PRIVATE
    Customer.cpp
    DayGui.cpp
    DayTime.cpp
    IngredientShop.cpp
    Inventory.cpp
    NightGui.cpp
    NightTime.cpp
    PotionShop.cpp
    TradeAgent.cpp
    UpgradeShop.cpp
)